target = 'S390'
target_c_sources = files('ffi.c')
target_asm_sources = files('sysv.S')

if run_command('../../meson-scripts/test-cc-uses-zarch.py',
               cc.cmd_array(), check: false).returncode() == 0
  ffi_conf.set('HAVE_AS_S390_ZARCH', 1)
endif
