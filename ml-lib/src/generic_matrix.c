#include<matrix.h>
#include<stdio.h>
#include<stdlib.h>

void ** create_new_matrix(size_t element_size, dimension_t rows, dimension_t columns)
{
    void **matrix;
    dimension_t r;
    if(rows==0 || columns==0) return NULL;
    matrix=(void **)malloc(sizeof(void *)*rows);
    if(matrix==NULL) return NULL;
    for(r=0;r<rows;++r)
    {
        matrix[r]=malloc(element_size*columns);
        if(matrix[r]==NULL)
        {
            for(--r;r>=0;--r) free(matrix[r]);
            free(matrix);
            return NULL;
        }
    }
    return matrix; 
}

void destroy_matrix(void **data, dimension_t rows)
{
    dimension_t r,c;
    if(!data) return;
    for(r=0;r<rows;++r)
    {
        if(data[r]) free(data[r]);
    }
    free(data);
}

// int main()
// {

//     return 0;
// }

