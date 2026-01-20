if host_cpu_family == 'x86_64'
  # 64-bit cpu, with or without 'x32' ilp32 mode.
  if host_system in ['cygwin', 'windows']
    target = 'X86_WIN64'
    target_c_sources = files('ffiw64.c')
    if is_msvc
      target_asm_sources = files('win64_intel.S')
    else
      target_asm_sources = files('win64.S')
    endif
  else
    target = 'X86_64'
    target_c_sources = files('ffi64.c', 'ffiw64.c')
    target_asm_sources = files('unix64.S', 'win64.S')
    if not cc.has_define('__ILP32__')
      tests_abis = [
        [],
        ['-DABI_NUM=FFI_GNUW64', '-DABI_ATTR=__MSABI__'],
      ]
    endif
  endif
else
  # 32-bit cpu.
  target_c_sources = files('ffi.c')
  if is_msvc
    target_asm_sources = files('sysv_intel.S')
  else
    target_asm_sources = files('sysv.S')
  endif
  if host_system in ['freebsd', 'openbsd']
    target = 'X86_FREEBSD'
  elif host_system in ['cygwin', 'windows', 'os/2', 'interix']
    target = 'X86_WIN32'
    if is_msvc
      extra_kwargs += {'masm_args': '/safeseh'}
    endif
  elif host_system in ['darwin']
    target = 'X86_DARWIN'
  else
    target = 'X86'
  endif
  if is_gnu_like
    tests_abis = [
      [],
      ['-DABI_NUM=FFI_STDCALL', '-DABI_ATTR=__STDCALL__'],
      ['-DABI_NUM=FFI_THISCALL', '-DABI_ATTR=__THISCALL__'],
      ['-DABI_NUM=FFI_FASTCALL', '-DABI_ATTR=__FASTCALL__'],
    ]
  endif
endif

if cc.compiles('asm (".text; foo: nop; .data; .long foo-.; .text");',
               name: 'ASM x86 PCREL')
  ffi_conf.set('HAVE_AS_X86_PCREL', 1)
endif
if run_command('../../meson-scripts/test-unwind-section.py',
               cc.cmd_array(), check: false).returncode() == 0
  ffi_conf.set('HAVE_AS_X86_64_UNWIND_SECTION_TYPE', 1)
endif
