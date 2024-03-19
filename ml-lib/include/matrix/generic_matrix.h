#pragma once
void ** create_new_matrix(size_t element_size, dimension_t rows, dimension_t columns);
void destroy_matrix(void **data, dimension_t rows);