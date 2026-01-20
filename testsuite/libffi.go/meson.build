if not cc.has_define('FFI_GO_CLOSURES', include_directories: ffiinc)
  subdir_done()
endif

suite_c_args = []
suite_tests = []

all_tests = files(
  'aa-direct.c',
  'closure1.c',
)

extra = [[]]
foreach f : all_tests
  suite_tests += [[f, extra]]
endforeach

tests += { 'go': [suite_tests, suite_c_args] }
