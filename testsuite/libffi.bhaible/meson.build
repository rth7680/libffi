suite_c_args = []
suite_tests = []

if is_msvc_like
  # -wd4996  suggest use of vsprintf_s instead of vsprintf
  # -wd4116  unnamed type definition
  # -wd4101  unreferenced local variable
  # -wd4244  implicit conversion to type of smaller size
  suite_c_args += ['-wd4996', '-wd4116', '-wd4101', '-wd4244']
else
  suite_c_args += cc.get_supported_arguments('-Wno-unused-variable',
                                             '-Wno-unused-parameter',
                                             '-Wno-unused-but-set-variable',
                                             '-Wno-uninitialized')
endif

extra = []
foreach i : range(1, 82)
  extra += f'-DDGTEST=@i@'
endforeach
suite_tests += [[files('test-call.c'), extra]]

if cc.get_define('FFI_CLOSURES', include_directories: ffiinc) != '0'
  extra = []
  foreach i : range(1, 81)
    extra += f'-DDGTEST=@i@'
  endforeach
  suite_tests += [[files('test-callback.c'), extra]]
endif

tests += { 'bhaible': [suite_tests, suite_c_args] }
