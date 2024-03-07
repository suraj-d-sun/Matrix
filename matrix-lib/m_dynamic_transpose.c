#include <stdio.h>
#include <stdlib.h>
#include "duration.h"

int ** create_matrix(int rows, int cols)
{
    int **x;
    int i, j;
    x=(int **)malloc(sizeof(int *) * rows);
    if (x==NULL) return NULL;
    for (i=0; i < rows; ++i)
    {
        x[i]=(int *)malloc(sizeof(int) * cols);
        if(x[i]==NULL)
        {
            for(j=0;j<i;j++) free(x[j]);
            free(x);
            return NULL;
        }
    }
    return x;
}

void destroy_matrix(int **x, int rows, int cols)
{
    int i;
    if(x==NULL) return;
    for(i=0; i < rows; i++)
    {
        if (x[i] != NULL) free(x[i]);
    }
    free(x);
}

int ** transpose_matrix(int **m,int r,int c)
{
    int r1,c1,r2,c2;
    int **tm;
    tm=create_matrix(c,r);
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
    c=create_matrix(*r3,*c3);
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
        destroy_matrix(tb,c2,r2);
    }
    return c;
}

int main(int argc, char *argv[])
{
    int **x;
    int **y;
    int **z;
    int r,c; // for result matrix rows, cols
    int i,j,k;
    struct timespec start_time,end_time;
    duration time_taken;
    int A_ROWS,A_COLS;
    int B_ROWS,B_COLS;
    int a_seed,a_increment;
    int b_seed,b_increment;
    if(argc!=9)
    {
        printf("Usage [m_dynamic.out r1 c1 r2 c2 a_seed a_incr b_seed b_incr]\n");
        return 0;
    }
    A_ROWS=atoi(argv[1]);
    A_COLS=atoi(argv[2]);
    B_ROWS=atoi(argv[3]);
    B_COLS=atoi(argv[4]);
    a_seed=atoi(argv[5]);
    a_increment=atoi(argv[6]);
    b_seed=atoi(argv[7]);
    b_increment=atoi(argv[8]);
    if(A_COLS!=B_ROWS)
    {
        printf("Dimensions are wrong");
        return 0;
    }
    x=create_matrix(A_ROWS,A_COLS);
    if(x==NULL)
    {
        printf("Low memory\n");
        return 0;
    }
    y=create_matrix(B_ROWS,B_COLS);
    if(y==NULL)
    {
        printf("Low memory\n");
        destroy_matrix(x,A_ROWS,A_COLS);
        return 0;
    }

    //code to populate data starts
    k=a_seed;
    for(r=0;r<A_ROWS;++r)
    {
        for(c=0;c<A_COLS;++c)
        {
            x[r][c]=k;
            k=k+a_increment;
        }
    }
    k=b_seed;
    for(r=0;r<B_ROWS;++r)
    {
        for(c=0;c<B_COLS;++c)
        {
            y[r][c]=k;
            k=k+b_increment;
        }
    }
    //code to populate data ends
    
    system("date");
    clock_gettime(CLOCK_MONOTONIC,&start_time);
    z=multiply_matrix(x,A_ROWS,A_COLS,y,B_ROWS,B_COLS,&r,&c);
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    time_taken=get_elapsed_time(start_time,end_time);
    if(z==NULL)
    {
        printf("Low Memory...\n");
        destroy_matrix(x,A_ROWS,A_COLS);
        destroy_matrix(y,B_ROWS,B_COLS);
        return 0;
    }
    printf("%u days, %u hours, %u minutes, %u seconds, %lu nano_sec\n", time_taken.days, time_taken.hours, time_taken.minutes, time_taken.seconds, time_taken.nanoseconds);
    system("date");
    if(r<10 && c<10)
    {
        for(i=0;i<r;++i)
        {
            for(j=0;j<c;++j)
            {
                printf("%8d",z[i][j]);
            }
            printf("\n");
        }
    }
    destroy_matrix(x,A_ROWS,A_COLS);
    destroy_matrix(y,B_ROWS,B_COLS);
    destroy_matrix(z,r,c);
    return 0;
}
