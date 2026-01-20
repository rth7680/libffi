target = 'MIPS'
target_c_sources = files('ffi.c')
target_asm_sources = files('o32.S', 'n32.S')

if host_system in ['linux', 'openbsd', 'freebsd']
  # Support 128-bit long double for NewABI.
  have_long_double = 'defined(__mips64)'
endif
