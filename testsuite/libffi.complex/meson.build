if not cc.has_define('FFI_TARGET_HAS_COMPLEX_TYPE',
                     include_directories: ffiinc)
  subdir_done()
endif

suite_c_args = []
suite_tests = []

all_tests = files(
  'cls_align_complex_double.c',
  'cls_align_complex_float.c',
  'cls_align_complex_longdouble.c',
  'cls_complex_double.c',
  'cls_complex_float.c',
  'cls_complex_longdouble.c',
  'cls_complex_struct_double.c',
  'cls_complex_struct_float.c',
  'cls_complex_struct_longdouble.c',
  'cls_complex_va_double.c',
  'cls_complex_va_float.c',
  'cls_complex_va_longdouble.c',
  'complex_double.c',
  'complex_float.c',
  'complex_int.c',
  'complex_longdouble.c',
  'many_complex_double.c',
  'many_complex_float.c',
  'many_complex_longdouble.c',
  'return_complex1_double.c',
  'return_complex1_float.c',
  'return_complex1_longdouble.c',
  'return_complex2_double.c',
  'return_complex2_float.c',
  'return_complex2_longdouble.c',
  'return_complex_double.c',
  'return_complex_float.c',
  'return_complex_longdouble.c',
)

extra = [[]]
foreach f : all_tests
  suite_tests += [[f, extra]]
endforeach

tests += { 'complex': [suite_tests, suite_c_args] }
