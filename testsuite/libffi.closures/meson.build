if cc.get_define('FFI_CLOSURES', include_directories: ffiinc) == '0'
  subdir_done()
endif

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

all_c = files(
  'closure_fn0.c',
  'closure_fn1.c',
  'closure_fn2.c',
  'closure_fn3.c',
  'closure_fn4.c',
  'closure_fn5.c',
  'closure_fn6.c',
  'closure_loc_fn0.c',
  'closure_simple.c',
  'cls_1_1byte.c',
  'cls_12byte.c',
  'cls_16byte.c',
  'cls_18byte.c',
  'cls_19byte.c',
  'cls_20byte1.c',
  'cls_20byte.c',
  'cls_24byte.c',
  'cls_2byte.c',
  'cls_3_1byte.c',
  'cls_3byte1.c',
  'cls_3byte2.c',
  'cls_3float.c',
  'cls_4_1byte.c',
  'cls_4byte.c',
  'cls_5_1_byte.c',
  'cls_5byte.c',
  'cls_6_1_byte.c',
  'cls_64byte.c',
  'cls_6byte.c',
  'cls_7_1_byte.c',
  'cls_7byte.c',
  'cls_8byte.c',
  'cls_9byte1.c',
  'cls_9byte2.c',
  'cls_align_double.c',
  'cls_align_float.c',
  'cls_align_longdouble.c',
  'cls_align_longdouble_split2.c',
  'cls_align_longdouble_split.c',
  'cls_align_pointer.c',
  'cls_align_sint16.c',
  'cls_align_sint32.c',
  'cls_align_sint64.c',
  'cls_align_uint16.c',
  'cls_align_uint32.c',
  'cls_align_uint64.c',
  'cls_dbls_struct.c',
  'cls_double.c',
  'cls_double_va.c',
  'cls_float.c',
  'cls_longdouble.c',
  'cls_longdouble_va.c',
  'cls_many_mixed_args.c',
  'cls_many_mixed_float_double.c',
  'cls_multi_schar.c',
  'cls_multi_sshort.c',
  'cls_multi_sshortchar.c',
  'cls_multi_uchar.c',
  'cls_multi_ushort.c',
  'cls_multi_ushortchar.c',
  'cls_pointer.c',
  'cls_pointer_stack.c',
  'cls_schar.c',
  'cls_sint.c',
  'cls_sshort.c',
  'cls_struct_va1.c',
  'cls_uchar.c',
  'cls_uint.c',
  'cls_uint_va.c',
  'cls_ulonglong.c',
  'cls_ulong_va.c',
  'cls_ushort.c',
  'err_bad_abi.c',
  'huge_struct.c',
  'nested_struct10.c',
  'nested_struct11.c',
  'nested_struct12.c',
  'nested_struct13.c',
  'nested_struct1.c',
  'nested_struct2.c',
  'nested_struct3.c',
  'nested_struct4.c',
  'nested_struct5.c',
  'nested_struct6.c',
  'nested_struct7.c',
  'nested_struct8.c',
  'nested_struct9.c',
  'nested_struct.c',
  'problem1.c',
  'single_entry_structs1.c',
  'single_entry_structs2.c',
  'single_entry_structs3.c',
  'stret_large2.c',
  'stret_large.c',
  'stret_medium2.c',
  'stret_medium.c',
  'testclosure.c',
)

all_cc = files(
  'unwindtest.cc',
  'unwindtest_ffi_call.cc',
)

extra = [[]]
foreach f : all_c
  suite_tests += [[f, extra]]
endforeach

# No C++ for or1k
if host_cpu_family != 'or1k'
  add_languages('cpp', native: false)
  foreach f : all_cc
    suite_tests += [[f, extra]]
  endforeach
endif

tests += { 'closures': [suite_tests, suite_c_args] }
