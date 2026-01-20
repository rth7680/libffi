target = 'SPARC'
if host_cpu_family == 'sparc'
  target_c_sources = files('ffi.c')
  target_asm_sources = files('v8.S')
  if cc.compiles('asm (".register %g2, #scratch");', name: 'ASM .register')
    ffi_conf.set('HAVE_AS_REGISTER_PSEUDO_OP', 1)
  endif
else
  target_c_sources = files('ffi64.c')
  target_asm_sources = files('v9.S')
endif

if cc.links('asm (".text; foo: nop; .data; .align 4; .byte 0; .uaword %r_disp32(foo); .text");',
            args: ['-fpic', '-shared'],
            name: 'ASM SPARC UA PCREL')
  ffi_conf.set('HAVE_AS_SPARC_UA_PCREL', 1)
endif
