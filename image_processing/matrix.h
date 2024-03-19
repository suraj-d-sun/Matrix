#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "duration.h"

void ** create_matrix(size_t element_size,int rows, int cols)
{
    void **x;
    int i, j;
    x=(void **)malloc(sizeof(void *) * rows);
    if (x==NULL) return NULL;
    for (i=0; i < rows; ++i)
    {
        x[i]=(void *)malloc(sizeof(element_size) * cols);
        if(x[i]==NULL)
        {
            for(j=0;j<i;j++) free(x[j]);
            free(x);
            return NULL;
        }
    }
    return x;
}

int ** create_matrix_int(int rows,int cols)
{
    return (int **)create_matrix(sizeof(int),rows,cols);
}

unsigned int ** create_matrix_uint(int rows,int cols)
{
    return (unsigned int **)create_matrix(sizeof(unsigned int),rows,cols);
}

unsigned char ** create_matrix_uchar(int rows,int cols)
{
    return (unsigned char **)create_matrix(sizeof(unsigned char),rows,cols);
}

double ** create_matrix_double(int rows,int cols)
{
    return (double **)create_matrix(sizeof(double),rows,cols);
}

void destroy_matrix(void **x, int rows, int cols)
{
    int i;
    if(x==NULL) return;
    for(i=0; i < rows; i++)
    {
        if (x[i] != NULL) free(x[i]);
    }
    free(x);
}

void destroy_matrix_double(double **v,int rows,int cols)
{
    destroy_matrix((void **)v,rows,cols);
}

void destroy_matrix_int(int **v,int rows,int cols)
{
    destroy_matrix((void **)v,rows,cols);
}

void destroy_matrix_uint(unsigned int **v,int rows,int cols)
{
    destroy_matrix((void **)v,rows,cols);
}

void destroy_matrix_uchar(unsigned char **v,int rows,int cols)
{
    destroy_matrix((void **)v,rows,cols);
}


int ** transpose_matrix(int **m,int r,int c)
{
    int r1,c1,r2,c2;
    int **tm;
    tm=create_matrix_int(c,r);
    if(tm==NULL) return NULL;
    for(r1=0;r1<r;++r1)
    {
        for(c1=0;c1<c;++c1)
        {
            tm[c1][r1]=m[r1][c1];           
        }
    }
    return tm;
}

int ** multiply_matrix(int **a, int r1, int c1, int **b, int r2, int c2, int *r3, int *c3)
{
    int **c;
    int **tb;
    int rr1, rr2, rr3, cc1, cc2, cc3, value;
    if(a==NULL || b==NULL || r3==NULL || c3==NULL || c1!=r2) return NULL;
    *r3=r1;
    *c3=c2;
    c=create_matrix_int(*r3,*c3);
    if(c==NULL) return NULL;
    int i,j;
    tb=transpose_matrix(b,r2,c2);
    if(tb==NULL)
    {
        for(rr1=0;rr1<r1;++rr1)
        {
            for(cc2=0;cc2<c2;++cc2)
            {
                value=0;
                for(rr2=0,cc1=0;cc1<c1;++cc1,++r2)
                {
                    value+=(a[rr1][cc1]*b[rr2][cc2]);
                }
                rr3=rr1;
                cc3=cc2;
                c[rr3][cc3]=value;
            }
        }
    }// if tb==NULL part ends
    else
    {
        for(rr1=0;rr1<r1;++rr1)
        {
            for(rr2=0;rr2<c2;++rr2)
            {
                value=0;
                for(cc1=0;cc1<c1;++cc1)
                {
                    value+=(a[rr1][cc1]*tb[rr2][cc1]);
                }
                c[rr1][rr2]=value;
            }
        }
        destroy_matrix((void **)tb,c2,r2);
    }
    return c;
}
