# No pthreads for windows or wasm
if is_msvc_like or host_cpu_family in ['wasm32', 'wasm64']
  subdir_done()
endif

suite_c_args = []
suite_tests = []

all_tests = files(
  'tsan.c',
)

extra = [[]]
foreach f : all_tests
  suite_tests += [[f, extra]]
endforeach

tests += { 'threads': [suite_tests, suite_c_args] }
