target_c_sources = files('ffi.c')
if host_system in ['cygwin', 'windows']
  target = 'ARM_WIN32'
  if is_msvc
    target_asm_sources = files('sysv_msvc_arm32.S')
  else
    target_asm_sources = files('sysv.S')
  endif
else
  target = 'ARM'
  target_asm_sources = files('sysv.S')
endif
