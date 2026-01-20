ffi_c_sources = files(
  'prep_cif.c',
  'types.c',
  'raw_api.c',
  'java_raw_api.c',
  'closures.c',
  'tramp.c',
)

if get_option('ffi-debug')
  ffi_c_sources += files('debug.c')
endif

if host_cpu_family in ['x86', 'x86_64']
  targetdir = 'x86'
elif host_cpu_family in ['parisc']
  targetdir = 'pa'
elif host_cpu_family in ['mips', 'mips64']
  targetdir = 'mips'
elif host_cpu_family in ['ppc', 'ppc64']
  targetdir = 'powerpc'
elif host_cpu_family in ['riscv32', 'riscv64']
  targetdir = 'riscv'
elif host_cpu_family in ['sh4']
  targetdir = 'sh'
elif host_cpu_family in ['sparc', 'sparc64']
  targetdir = 'sparc'
elif host_cpu_family in ['wasm32', 'wasm64']
  targetdir = 'wasm'
else
  targetdir = host_cpu_family
endif

subdir(targetdir)

ffiinc = include_directories('..', '../include', targetdir)

if is_msvc
  # MSVC cannot compile assembly files directly. They need to be
  # preprocessed with the C compiler first, then compiled with MASM.
  target_asm_sources = cc.preprocess(target_asm_sources,
                                     output: '@BASENAME@.masm',
                                     include_directories: ffiinc)
  add_languages('masm', native: false)
endif

ffi_link_args = []
ffi_map_file = []

if get_option('ffi-build-versioned')
  libffi_map_in = meson.project_source_root() / 'libffi.map.in'
  arg_prefix = '-Wl,--version-script='
  if cc.has_multi_link_arguments(['-shared', arg_prefix + libffi_map_in])
    ffi_map_file = cc.preprocess(libffi_map_in,
                                 output: '@BASENAME@',
                                 include_directories: ffiinc)
    ffi_map_abs = ffi_map_file[0].full_path()
    ffi_link_args += arg_prefix + ffi_map_abs
  endif
endif

public_c_args = []
if get_option('default_library') == 'static'
  public_c_args += ['-DFFI_STATIC_BUILD']
endif

ffi_lib = library('ffi', ffi_c_sources, target_c_sources, target_asm_sources,
  c_args : ['-DFFI_BUILDING_DLL', public_c_args],
  include_directories : ffiinc,
  link_args: ffi_link_args,
  link_depends: ffi_map_file,
  version : ffi_version,
  soversion : ffi_soversion,
  darwin_versions : ffi_darwin_versions,
  install : true,
  kwargs: extra_kwargs,
)

pkgconf = import('pkgconfig')
pkgconf.generate(ffi_lib,
  description : 'Library supporting Foreign Function Interfaces',
  filebase : 'libffi',
  extra_cflags: public_c_args)

ffi_dep = declare_dependency(link_with : ffi_lib,
  compile_args: public_c_args,
  include_directories : ffiinc)

meson.override_dependency('libffi', ffi_dep)
