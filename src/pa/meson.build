if host_system == 'hpux'
  if host_cpu_family == 'hppa'
    target = 'PA_HPUX'
    target_c_sources = files('ffi.c')
    target_asm_sources = files('hpux32.S')
  else
    target = 'PA64_HPUX'
    target_c_sources = files('ffi64.c')
    target_asm_sources = files('hpux64.S')
  endif
else
  target = 'PA_LINUX'
  target_c_sources = files('ffi.c')
  target_asm_sources = files('linux.S')
endif
