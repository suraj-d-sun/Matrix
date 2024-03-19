#pragma once
typedef struct __mat_int8 mat_int8; //opaque type

mat_int8 * mat_int8_create_new(dimension_t rows, dimension_t columns);

mat_int8 * mat_int8_create_new_filled(dimension_t rows, dimension_t columns, int8_t fill_value);

void mat_int8_destroy(mat_int8 *matrix);

void mat_int8_set(mat_int8 *matrix, index_t row_index, index_t column_index,int8_t value);

int8_t mat_int8_get(mat_int8 *matrix,index_t row_index, index_t column_index);

void mat_int8_get_dimensions(mat_int8 *matrix, dimension_t *rows, dimension_t *columns);

mat_int8 * mat_int8_transpose(mat_int8 *matrix);

mat_int8 * mat_int8_matrix_multiplication(mat_int8 *left_matrix,mat_int8 *right_matrix);

mat_int8 * mat_int8_scalar_multiplication(int8_t value, mat_int8 *matrix);

mat_int8 * mat_int8_matrix_addition(mat_int8 *left_matrix,mat_int8 *right_matrix);

mat_int8 * mat_int8_matrix_subtraction(mat_int8 *left_matrix,mat_int8 *right_matrix);

int mat_int8_to_csv(mat_int8 *matrix, const char *csv_file_name);