#include <matrix.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct __mat_int8
{
    dimension_t rows;
    dimension_t columns;
    int8_t **data;
} mat_int8;

mat_int8 *mat_int8_create_new(dimension_t rows, dimension_t columns)
{
    mat_int8 *matrix;
    int8_t **data;
    data = (int8_t **)create_new_matrix(sizeof(int8_t), rows, columns);
    if (!data) return NULL;
    matrix = (mat_int8 *)malloc(sizeof(mat_int8));
    if (!matrix)
    {
        destroy_matrix((void **)data, rows);
        return NULL;
    }
    matrix->data = data;
    matrix->rows = rows;
    matrix->columns = columns;
    return matrix;
}

mat_int8 * mat_int8_create_new_filled(dimension_t rows, dimension_t columns, int8_t fill_value)
{
    index_t r,c;
    mat_int8 *matrix;
    int8_t *ptr;
    matrix = mat_int8_create_new(rows, columns);
    if (!matrix) return NULL;
    for (r = 0; r < matrix->rows; ++r)
    {
        for (ptr = matrix->data[r], c = 0; c < matrix->columns; ++c, ++ptr)
        {
            *ptr = fill_value;
        }
    }
    return matrix;
}

void mat_int8_destroy(mat_int8 * matrix)
{
    if (!matrix) return;
    destroy_matrix((void **)(matrix->data),matrix->rows);
    free(matrix);
}

void mat_int8_set(mat_int8 *matrix, index_t row_index, index_t column_index,int8_t value) 
{
    if(!matrix || row_index>=matrix->rows || column_index>=matrix->columns) return; 
    matrix->data[row_index][column_index]=value;
}

int8_t mat_int8_get(mat_int8 *matrix, index_t row_index, index_t column_index)
{ 
    int8_t value=0;
    if(!matrix || row_index>=matrix->rows || column_index>=matrix->columns) return value; 
    value=matrix->data[row_index][column_index];
    return value;
}

void mat_int8_get_dimensions(mat_int8 *matrix, dimension_t *rows, dimension_t *columns)
{
    if(rows) *rows=0;
    if(columns) *columns=0;
    if(!matrix) return;
    *rows=matrix->rows;
    *columns=matrix->columns;
}

mat_int8 * mat_int8_transpose(mat_int8 *matrix) 
{
    mat_int8 *transposed_matrix;
    index_t r,c;
    if(!matrix) return NULL;
    transposed_matrix=mat_int8_create_new(matrix->columns,matrix->rows);
    if(!transposed_matrix) return NULL;
    for(r=0;r<matrix->rows;++r)
    {
        for(c=0;c<matrix->columns;++c)
        {
            transposed_matrix->data[c][r]=matrix->data[r][c];
        }
    }
    return transposed_matrix;
}

mat_int8 * mat_int8_matrix_multiplication(mat_int8 *left_matrix,mat_int8 *right_matrix) 
{
    // right now zero optimzation applied, will implement later on
    mat_int8 *product_matrix;
    int8_t value;
    index_t r1, r2, c1, c2, r3,c3;
    if(!left_matrix || !right_matrix || left_matrix->columns!=right_matrix->rows) return NULL; 
    product_matrix=mat_int8_create_new(left_matrix->rows, right_matrix->columns);
    if (product_matrix==NULL) return NULL;
    for(r1=0;r1<left_matrix->rows;++r1)
    { 
        for(c2=0;c2<right_matrix->columns;++c2)
        {
            value=0;
            for(r2=0,c1=0;c1<left_matrix->columns; ++c1,++r2)
            {
                value=value+(left_matrix->data[r1][c1]*right_matrix->data[r2][c2]);
            }
            r3=r1;
            c3=c2;
            product_matrix->data[r3][c3]=value;
        }
    }
    return product_matrix;
}

mat_int8 * mat_int8_scalar_multiplication(int8_t scalar_value,mat_int8 *matrix) 
{
    // right now zero optimzation applied, will implement later on
    mat_int8 *product_matrix;
    index_t r,c;    
    if(!matrix) return NULL;
    product_matrix=mat_int8_create_new(matrix->rows, matrix->columns); 
    if (product_matrix==NULL) return NULL;    
    for(r=0;r<matrix->rows;++r)
    {
        for(c=0;c<matrix->columns;++c)
        {
            product_matrix->data[r][c]=scalar_value*matrix->data[r][c];
        } 
    }
    return product_matrix;
}

mat_int8 * mat_int8_matrix_addition(mat_int8 *left_matrix,mat_int8 *right_matrix)
{
    mat_int8 *sum_matrix;
    index_t r,c;
    dimension_t rows,columns;
    if(!left_matrix || !right_matrix || left_matrix->rows!=right_matrix->rows || left_matrix->columns!=right_matrix->columns) return NULL;
    sum_matrix=mat_int8_create_new(left_matrix->rows,left_matrix->columns);
    if(!sum_matrix) return 0;
    rows=left_matrix->rows;
    columns=left_matrix->columns;
    for(r=0;r<rows;++r)
    {
        for(c=0;c<columns; ++c)
        {
            sum_matrix->data[r][c]=left_matrix->data[r][c]+right_matrix->data[r][c];
        }
    }
    return sum_matrix;
}

mat_int8 * mat_int8_matrix_subtraction(mat_int8 *left_matrix,mat_int8 *right_matrix)
{
    mat_int8 *diff_matrix;
    index_t r,c;
    dimension_t rows,columns;
    if(!left_matrix || !right_matrix || left_matrix->rows!=right_matrix->rows || left_matrix->columns!=right_matrix->columns) return NULL;
    diff_matrix=mat_int8_create_new(left_matrix->rows,left_matrix->columns);
    if(!diff_matrix) return 0;
    rows=left_matrix->rows;
    columns=left_matrix->columns;
    for(r=0;r<rows;++r)
    {
        for(c=0;c<columns; ++c)
        {
            diff_matrix->data[r][c]=left_matrix->data[r][c]-right_matrix->data[r][c];
        }
    }
    return diff_matrix;
}

int mat_int8_to_csv(mat_int8 *matrix, const char *csv_file_name)
{
    FILE *f;
    index_t r,c;
    dimension_t rows, columns;
    if(!matrix) return -1;
    rows=matrix->rows;
    columns=matrix->columns-1; // it is a trick
    f=fopen(csv_file_name, "w");
    if(!f) return -1;
    fputs("mat_int8\r\n",f);
    for(r=0;r<rows;++r)
    {
        for(c=0;c<columns;++c)
        {
            fprintf(f, "%" PRId8 ",", matrix->data[r][c]);
        }
        fprintf(f, "%" PRId8 "\r\n", matrix->data[r][c]);
    }
    fclose(f);
    return 0;
}

// //testing purpose only
// void mat_int8_print(mat_int8 *matrix, const char *title)
// {
//     dimension_t rows,columns;
//     index_t r,c;
//     printf("---------------- %s ---------------\n", title);
//     mat_int8_get_dimensions(matrix, &rows,&columns);
//     printf("Rows %" PRId8 " and columns %" PRId8 "\n",rows,columns);
//     for(r=0;r<rows;++r)
//     {
//         for(c=0;c<columns;++c)
//         {
//             printf("%10" PRId8 "", matrix->data[r][c]);
//         }
//         printf("\n");
//     }
// }

// // following is just for testing, should be commented before creating library file
// void mat_int8_test()
// {
//     mat_int8 *matrix;
//     mat_int8 *transposed_matrix;
//     mat_int8 *filled_matrix;
//     mat_int8 *a_matrix;
//     mat_int8 *b_matrix;
//     mat_int8 *c_matrix;
//     mat_int8 *d_matrix;
//     mat_int8 *p_matrix;
//     mat_int8 *q_matrix;
//     mat_int8 *r_matrix;
//     mat_int8 *s_matrix;
//     index_t r,c;
//     dimension_t rows, columns;
//     int8_t value;
//     matrix=mat_int8_create_new(5,4);
//     if (matrix==NULL)
//     {
//         printf("Unable to create mat_int8 type matrix\n"); 
//         return;
//     }
//     mat_int8_get_dimensions(matrix,&rows,&columns);
//     value=1;
//     for(r=0;r<rows;++r)
//     {
//         for(c=0;c<columns;++c)
//         {    
//             mat_int8_set(matrix,r,c,value); 
//             ++value;
//         }
//     } 
//     mat_int8_print(matrix, "matrix");
//     transposed_matrix=mat_int8_transpose(matrix);
//     if (transposed_matrix)
//     {
//         mat_int8_print(transposed_matrix, "transposed_matrix");
//     }
//     else
//     {
//         printf("Unable to create transposed matrix\n");
//     }
//     filled_matrix=mat_int8_create_new_filled(8,3,123); 
//     if(filled_matrix) 
//     {
//         mat_int8_print(filled_matrix, "filled_matrix");
//     }
//     else
//     {  
//         printf("Unable to create filled matrix\n");
//     }
//         a_matrix=mat_int8_create_new(2,3); 
//         if(!a_matrix)
//         {
//             printf("Cannot create a_matrix\n");
//         }
//         b_matrix=mat_int8_create_new(3,4); 
//         if(!b_matrix)
//         {
//             printf("Cannot create b_matrix\n");
//         }
//         if(a_matrix)
//         {
//             value=1;
//             for(r=0;r<a_matrix->rows;++r)
//             {
//                 for(c=0;c<a_matrix->columns;++c)
//                 {
//                     mat_int8_set(a_matrix,r,c,value);
//                     if(value%2==0) ++value;
//                     else --value;
//                 }
//             }
//         }
//         if(b_matrix)
//         {
//             value=1;
//             for(r=0;r<b_matrix->rows;++r)
//             {
//                 for(c=0;c<b_matrix->columns;++c)
//                 {
//                     mat_int8_set(b_matrix,r,c,value);
//                     if(value%2!=0) ++value;
//                     else --value;
//                 }
//             }
//         }
//         if(a_matrix)
//         {
//             mat_int8_print(a_matrix,"a_matrix");
//         }
//         if(b_matrix)
//         {
//             mat_int8_print(b_matrix,"b_matrix");
//         }
//         c_matrix=mat_int8_matrix_multiplication(a_matrix,b_matrix); 
//         if(c_matrix==NULL)
//         {
//             printf("Unable to compute product of a_matrix and b_matrix\n"); 
//         }
//         else
//         {
//             mat_int8_print(c_matrix, "product: c_matrix"); 
//         }
//         value=1;
//         for(r=0;r<c_matrix->rows;++r)
//         {
//             for(c=0;c<c_matrix->columns;++c)
//             {
//                 mat_int8_set(c_matrix,r,c,value); 
//                 ++value;
//             } 
//         }
//         d_matrix=mat_int8_scalar_multiplication(10,c_matrix); 
//         if(!d_matrix)
//         {
//             printf("Unable to perform scalar multiplication\n");
//         }
//         else
//         {  
//             mat_int8_print(d_matrix, "scalar matrix multiplication: d_matrix");
//         }
//         p_matrix=mat_int8_create_new(3,3);
//         if(p_matrix)
//         {
//             value=10;
//             for(r=0;r<p_matrix->rows;++r)
//             {
//                 for(c=0;c<p_matrix->columns;++c)
//                 {
//                     mat_int8_set(p_matrix,r,c,value);
//                     value+=10;
//                 }
//             } 
//         }
//         q_matrix=mat_int8_create_new(3,3);
//         if(q_matrix)        
//         {
//             value=1;
//             for(r=0;r<q_matrix->rows;++r)
//             {
//                 for(c=0;c<q_matrix->columns;++c)
//                 {
//                     mat_int8_set(q_matrix,r,c,value);
//                     value+=1;
//                 }
//             } 
//         }
//         r_matrix=mat_int8_matrix_addition(p_matrix,q_matrix);
//         if(r_matrix)
//         {
//             mat_int8_print(r_matrix,"addition : r_matrix");
//         }
//         else
//         {
//             printf("Unable to perform the addition\n");
//         }
//         s_matrix=mat_int8_matrix_subtraction(p_matrix,q_matrix); 
//         if(s_matrix)
//         {
//             mat_int8_print(s_matrix, "subtraction : s_matrix"); 
//             if(mat_int8_to_csv(s_matrix, "data.csv")==-1) 
//             {
//                 printf("Unable to save s_matrix to data.csv\n");
//             }
//             else
//             {
//                 printf("data.csv created with s_matrix\n");
//             }
//         }
//         else
//         {
//             printf("Unable to perform subtraction\n");
//         } 
//         mat_int8_destroy(a_matrix);
//         mat_int8_destroy(b_matrix);
//         mat_int8_destroy(c_matrix);
//         mat_int8_destroy(d_matrix);
//         mat_int8_destroy(matrix);
//         mat_int8_destroy(transposed_matrix);
//         mat_int8_destroy(filled_matrix);
//         mat_int8_destroy(p_matrix);
//         mat_int8_destroy(q_matrix);
//         mat_int8_destroy(r_matrix);
//         mat_int8_destroy(s_matrix);
// }

// int main()
// {
//     mat_int8_test();
//     return 0;
// }


