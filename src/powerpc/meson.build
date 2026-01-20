if host_system == 'aix'
  target = 'POWERPC_AIX'
  target_c_sources = files('ffi_darwin.c')
  target_asm_sources = files('aix.S', 'aix_closure.S')
elif host_system == 'darwin'
  target = 'POWERPC_DARWIN'
  target_c_sources = files('ffi_darwin.c')
  target_asm_sources = files('darwin.S', 'darwin_closure.S')
elif host_cpu_family == 'ppc'
  # 32-bit cpu
  if host_system in ['freebsd', 'openbsd', 'netbsd']
    target = 'POWERPC_FREEBSD'
  else
    target = 'POWERPC'
  endif
  target_c_sources = files('ffi.c', 'ffi_sysv.c')
  target_asm_sources = files('sysv.S', 'ppc_closure.S')
  if cc.has_define('__SPE__')
    add_project_arguments('-D__NO_FPRS__', language: 'c')
  else
    have_long_double_variant = true
  endif
else
  # 64-bit cpu
  target = 'POWERPC'
  target_c_sources = files('ffi.c', 'ffi_linux64.c')
  target_asm_sources = files('linux64.S', 'linux64_closure.S')
  have_long_double_variant = true
endif
