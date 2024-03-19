copy ../../include/matrix/mat_int8_matrix.h header_int8_template.h
copy ../../src/mat_int8_matrix.c src_int8_template.c

sed "s/int8/uint8/g" header_int8_template.h > include/mat_uint8_matrix.h
sed "s/int8/uint8/g" src_int8_template.c > src/mat_uint8_matrix.c
sed -i "s/PRId8/PRIu8/g" src/mat_uint8_matrix.c

sed "s/int8/int16/g" header_int8_template.h > include/mat_int16_matrix.h
sed "s/int8/int16/g" src_int8_template.c > src/mat_int16_matrix.c
sed -i "s/PRId8/PRId16/g" src/mat_int16_matrix.c

sed "s/int8/uint16/g" header_int8_template.h > include/mat_uint16_matrix.h
sed "s/int8/uint16/g" src_int8_template.c > src/mat_uint16_matrix.c 
sed -i "s/PRId8/PRIu16/g" src/mat_uint16_matrix.c

sed "s/int8/int32/g" header_int8_template.h > include/mat_int32_matrix.h
sed "s/int8/int32/g" src_int8_template.c > src/mat_int32_matrix.c
sed -i "s/PRId8/PRId32/g" src/mat_int32_matrix.c

sed "s/int8/uint32/g" header_int8_template.h > include/mat_uint32_matrix.h
sed "s/int8/uint32/g" src_int8_template.c > src/mat_uint32_matrix.c
sed -i "s/PRId8/PRIu32/g" src/mat_uint32_matrix.c

sed "s/int8/int64/g" header_int8_template.h > include/mat_int64_matrix.h
sed "s/int8/int64/g" src_int8_template.c > src/mat_int64_matrix.c
sed -i "s/PRId8/PRId64/g" src/mat_uint64_matrix.c

sed "s/int8/uint64/g" header_int8_template.h > include/mat_uint64_matrix.h
sed "s/int8/uint64/g" src_int8_template.c > src/mat_uint64_matrix.c
sed -i "s/PRId8/PRIu64/g" src/mat_uint64_matrix.c

sed "s/int8/double/g" header_int8_template.h > include/mat_double_matrix.h
sed "s/int8/double/g" src_int8_template.c > src/mat_double_matrix.c
sed -i "s/PRId8/PRIlf/g" src/mat_double_matrix.c

sed "s/int8/long_double/g" header_int8_template.h > include/mat_long_double_matrix.h
sed "s/int8/long_double/g" src_int8_template.c > src/mat_long_double_matrix.c
sed -i "s/PRId8/PRIlf/g" src/mat_double_matrix.c

sed "s/int8/char/g" header_int8_template.h > include/mat_char_matrix.h
sed "s/int8/char/g" src_int8_template.c > src/mat_char_matrix.c
sed -i "s/PRId8/PRIc/g" src/mat_char_matrix.c

sed "s/int8/uchar/g" header_int8_template.h > include/mat_uchar_matrix.h
sed "s/int8/uchar/g" src_int8_template.c > src/mat_uchar_matrix.c
sed -i "s/PRId8/PRIc/g" src/mat_uchar_matrix.c

copy include/* ../../include/matrix
copy src/* ../../src





