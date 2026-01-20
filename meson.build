project('libffi', 'c', version: '3.5.2',
        meson_version: '>= 1.3',
        default_options: ['debug=true',
                          'optimization=3',
                          'warning_level=1'])

fs = import('fs')

libtool_version = run_command('meson-scripts/extract-libtool-version.py',
  meson.current_source_dir() / 'libtool-version',
  check: true).stdout().strip().split(':')
current = libtool_version[0].to_int()
revision = libtool_version[1].to_int()
age = libtool_version[2].to_int()
ffi_version = '@0@.@1@.@2@'.format(current - age, age, revision)
ffi_soversion = '@0@'.format(current - age)
ffi_darwin_versions = '@0@'.format(current + 1)

# NOTE: host = "cross" or "target"
host_cpu_family = host_machine.cpu_family()
host_system = host_machine.system()

cc = meson.get_compiler('c')
is_msvc = cc.get_id() == 'msvc'
is_msvc_like = cc.get_argument_syntax() == 'msvc'
is_gnu_like = cc.get_argument_syntax() == 'gcc'

if is_gnu_like
  add_project_arguments('-fexceptions', language: 'c')
endif

ffi_conf = configuration_data()

if host_machine.endian() == 'big'
  ffi_conf.set('WORDS_BIGENDIAN', 1)
endif

headers = [
  'alloca.h',
  'stdint.h',
  'inttypes.h',
]
foreach h : headers
  if cc.has_header(h)
    ffi_conf.set('HAVE_' + h.underscorify().to_upper(), 1)
  endif
endforeach

if cc.has_function('memfd_create', prefix: ['#define _GNU_SOURCE',
                                            '#include <sys/mman.h>'])
  ffi_conf.set('HAVE_MEMFD_CREATE', 1)
endif

# Default values, modified in within src/.
target_c_sources = []
target_asm_sources = []
tests_abis = [[]]
masm_args = []
targetdir = ''
have_long_double = ''
have_long_double_variant = false
extra_kwargs = {}

subdir('src')

if have_long_double == ''
  size_long_double = cc.sizeof('long double')
  if size_long_double > 0
    if have_long_double_variant
      ffi_conf.set('HAVE_LONG_DOUBLE_VARIANT', 1)
      ffi_conf.set('HAVE_LONG_DOUBLE', 1)
    elif size_long_double != cc.sizeof('double')
      ffi_conf.set('HAVE_LONG_DOUBLE', 1)
    endif
  endif
else
  ffi_conf.set('HAVE_LONG_DOUBLE', have_long_double)
endif

subdir('include')

if host_machine.endian() == 'big'
  ffi_conf.set('WORDS_BIGENDIAN', 1)
endif

# Assembly directive support
if cc.compiles('asm (".cfi_sections\\n.cfi_startproc\\n.cfi_endproc");',
               name: 'ASM .cfi')
  ffi_conf.set('HAVE_AS_CFI_PSEUDO_OP', 1)
endif

ptrauth_code = '''
#ifdef __clang__
# if __has_feature(ptrauth_calls)
#  define HAVE_PTRAUTH 1
# endif
#endif

#ifndef HAVE_PTRAUTH
# error Pointer authentication not supported
#endif
'''

if cc.compiles(ptrauth_code)
  ffi_conf.set('HAVE_PTRAUTH', 1)
endif

if get_option('pax_emutramp')
  ffi_conf.set('FFI_MMAP_EXEC_EMUTRAMP_PAX', 1)
endif

if cc.symbols_have_underscore_prefix()
  ffi_conf.set('SYMBOL_UNDERSCORE', 1)
endif

if host_cpu_family in ['arm', 'aarch64'] and host_system == 'darwin'
  message('Cannot use PROT_EXEC on this target, using fallback')
  ffi_conf.set('FFI_EXEC_TRAMPOLINE_TABLE', 1)
elif host_system in ['android', 'darwin', 'openbsd', 'freebsd', 'solaris', 'qnx']
  message('Cannot use malloc on this target, using fallback')
  ffi_conf.set('FFI_MMAP_EXEC_WRIT', 1)
endif

if host_system == 'windows' and is_gnu_like
  # so printf supports long double under mingw-w64 (used in cls_longdouble_va)
  add_project_arguments('-D__USE_MINGW_ANSI_STDIO=1', language: 'c')
endif

if is_gnu_like
  no_lto = cc.get_supported_arguments('-fno-lto')
  if run_command('meson-scripts/test-ro-eh-frame.py',
                 cc.cmd_array(), '-fpic', '-fexceptions', no_lto,
                 check: false).returncode() == 0
    ffi_conf.set_quoted('EH_FRAME_FLAGS', 'aw')
  else
    ffi_conf.set('HAVE_RO_EH_FRAME', 1)
    ffi_conf.set_quoted('EH_FRAME_FLAGS', 'a')
  endif
endif

if cc.has_function_attribute('visibility')
  t = 'meson-scripts/test-cc-supports-hidden-visibility.py'
  if run_command(t, cc.cmd_array(), check: false).returncode() == 0
    message('.hidden pseudo-op is available')
    ffi_conf.set('HAVE_HIDDEN_VISIBILITY_ATTRIBUTE', 1)
  else
    message('.hidden pseudo-op is NOT available')
  endif
endif

# User options
if get_option('ffi-debug')
  ffi_conf.set('FFI_DEBUG', 1)
endif
if not get_option('structs')
  ffi_conf.set('FFI_NO_STRUCTS', 1)
endif
if not get_option('raw_api')
  ffi_conf.set('FFI_NO_RAW_API', 1)
endif
if get_option('exe_static_tramp')
  if host_system == 'cygwin'
    # Only define static trampolines if we are using the cygwin runtime.
    # Will this need to be changed for mingw?
    if is_gnu_like
      ffi_conf.set('FFI_EXEC_STATIC_TRAMP', 1)
    endif
  elif host_system == 'linux' and host_cpu_family in ['arm', 'aarch64', 'x86', 'x86_64', 'loongarch']
    ffi_conf.set('FFI_EXEC_STATIC_TRAMP', 1)
  endif
endif
if get_option('purify_safety')
  ffi_conf.set('USING_PURIFY', 1)
endif

# Configure fficonfig.h (not installed)
configure_file(output : 'fficonfig.h', configuration : ffi_conf)

if get_option('doc')
  subdir('doc')
endif

if get_option('tests')
  subdir('testsuite')
endif

install_man([
  'man/ffi.3',
  'man/ffi_call.3',
  'man/ffi_prep_cif.3',
  'man/ffi_prep_cif_var.3'])

summary({
  'Host CPU': host_machine.cpu(),
  'Host CPU family': host_cpu_family,
  'Host system': host_system,
  'Target': target,
})
