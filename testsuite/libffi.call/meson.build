suite_c_args = []
suite_tests = []

if is_msvc_like
  # -wd4005  macro redefinition
  # -wd4244  implicit conversion to type of smaller size
  # -wd4305  truncation to smaller type
  # -wd4477  printf %lu of uintptr_t
  # -wd4312  implicit conversion to type of greater size
  # -wd4311  pointer truncation to unsigned long
  # -EHsc    C++ Exception Handling (no SEH exceptions)
  suite_c_args += ['-wd4005', '-wd4244', '-wd4305', '-wd4477',
                   '-wd4312', '-wd4311', '-EHsc']
endif

all_tests = files(
  'align_mixed.c',
  'align_stdcall.c',
  'bpo_38748.c',
  'callback2.c',
  'callback3.c',
  'callback4.c',
  'callback.c',
  'err_bad_typedef.c',
  'float1.c',
  'float2.c',
  'float3.c',
  'float4.c',
  'float.c',
  'float_va.c',
  'longjmp.c',
  'many2.c',
  'many.c',
  'many_double.c',
  'many_mixed.c',
  'negint.c',
  'offsets.c',
  'overread.c',
  'pr1172638.c',
  'promotion.c',
  'pyobjc_tc.c',
  'return_dbl1.c',
  'return_dbl2.c',
  'return_dbl.c',
  'return_fl1.c',
  'return_fl2.c',
  'return_fl3.c',
  'return_fl.c',
  'return_ldl.c',
  'return_ll1.c',
  'return_ll.c',
  'return_sc.c',
  'return_sl.c',
  'return_uc.c',
  'return_ul.c',
  's55.c',
  'strlen2.c',
  'strlen3.c',
  'strlen4.c',
  'strlen.c',
  'struct10.c',
  'struct1.c',
  'struct2.c',
  'struct3.c',
  'struct4.c',
  'struct5.c',
  'struct6.c',
  'struct7.c',
  'struct8.c',
  'struct9.c',
  'struct_by_value_2.c',
  'struct_by_value_3.c',
  'struct_by_value_3f.c',
  'struct_by_value_4.c',
  'struct_by_value_4f.c',
  'struct_by_value_big.c',
  'struct_by_value_small.c',
  'struct_int_float.c',
  'struct_return_2H.c',
  'struct_return_8H.c',
  'uninitialized.c',
  'va_1.c',
  'va_2.c',
  'va_3.c',
  'va_struct1.c',
  'va_struct2.c',
  'va_struct3.c',
  'x32.c',
)

extra = [[]]
foreach f : all_tests
  suite_tests += [[f, extra]]
endforeach

tests += { 'call': [suite_tests, suite_c_args] }
