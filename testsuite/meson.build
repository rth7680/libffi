tests = { }

subdir('libffi.bhaible')
subdir('libffi.call')
subdir('libffi.closures')
subdir('libffi.complex')
subdir('libffi.go')
subdir('libffi.threads')

# We generate a full set of tests for each optimization
tests_optimizations = ['0', '2']

common_c_args = []
if is_gnu_like
  common_c_args = cc.get_supported_arguments('-W', '-Wall', '-Wno-psabi')
endif

foreach suite, suite_params : tests
  assert(suite_params.length() == 2)
  suite_tests = suite_params[0]
  suite_c_args = suite_params[1]
  assert(suite_tests.length() > 0)

  foreach one_test : suite_tests
    assert(one_test.length() == 2)
    file = one_test[0]
    extra_c_args = one_test[1]
    base_name = fs.stem(file)

    this_abis = fs.read(file).contains('ABI_NUM') ? tests_abis : [[]]
    assert(this_abis.length() > 0)
    assert(extra_c_args.length() > 0)

    foreach one_abi : this_abis
      foreach one_extra : extra_c_args
        matrix_c_args = []
        matrix_c_args += one_abi
        matrix_c_args += one_extra

        foreach one_opt : tests_optimizations
          test_name = base_name
          exe_name = base_name
          if matrix_c_args != []
            test_name += ' ' + ' '.join(matrix_c_args)
            exe_name += ''.join(matrix_c_args)
          endif
          test_name += f' -O@one_opt@'
          exe_name += f'-O@one_opt@'
          exe_name = exe_name.underscorify()
            
          exe = executable(exe_name, file,
            dependencies: ffi_dep,
            c_args: [common_c_args, suite_c_args, matrix_c_args],
            override_options: [f'optimization=@one_opt@'],
          )
          test(test_name, exe, suite: suite)
        endforeach
      endforeach
    endforeach
  endforeach
endforeach
