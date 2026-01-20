target_c_sources = files('ffi.c')
if host_system in ['cygwin', 'windows']
  target = 'ARM_WIN64'
  if is_msvc
    target_asm_sources = files('win64_armasm.S')
  else
    target_asm_sources = files('sysv.S')
  endif
else
  target = 'AARCH64'
  target_asm_sources = files('sysv.S')
endif
