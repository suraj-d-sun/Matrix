// Implementation by Sir
#include <stdio.h>
#include <stdlib.h>
int **create_matrix(int rows, int cols)
{
    int **x;
    int i, j;
    x = (int **)malloc(sizeof(int *) * rows);
    if (x == NULL)
        return NULL;
    for (i = 0; i < rows; ++i)
    {
        x[i] = (int *)malloc(sizeof(int) * cols);
        if (x[i] == NULL)
        {
            for (j = 0; j < i; j++)
                free(x[j]);
            free(x);
            return NULL;
        }
    }
    return x;
}

void destroy_matrix(int **x, int rows, int cols)
{
    int i;
    if (x == NULL)
        return;
    for (i = 0; i < rows; i++)
    {
        if (x[i] != NULL)
            free(x[i]);
    }
    free(x);
}

int **multiply_matrix(int **a, int r1, int c1, int **b, int r2, int c2, int *r3, int *c3)
{
    int **c;
    int rr1, rr2, rr3, cc1, cc2, cc3, value;
    if(a==NULL || b==NULL || r3==NULL || c3==NULL || c1!=r2) return NULL;
    *r3=r1;
    *c3=c2;
    c=create_matrix(*r3,*c3);
    if(c==NULL) return NULL;
    for(rr1=0; rr1<r1;++rr1)
    {
        for(cc2=0;cc2<c2;++c2)
        {
            value=0;
            for(rr2=0,cc1=0;cc1<c1;++cc1,++rr2)
            {
                value+=a[rr1][cc1]*b[rr2][cc2];
            }
            rr3=rr1;
            cc3=cc2;
            c[rr3][cc3]=value;
        }
    }
    return c;
}

int main()
{
    int **x;
    int **y;
    int **z;
    int r,c; // for result matrix rows, cols
    int i,j;
    x=create_matrix(4,5);
    if(x==NULL)
    {
        printf("Low memory\n");
        return 0;
    }
    y=create_matrix(5,2);
    if(y==NULL)
    {
        printf("Low memory\n");
        destroy_matrix(x,4,5);
        return 0;
    }
    x[0][0]=1;
    x[0][1]=2;
    x[0][2]=3;
    x[0][3]=4;
    x[0][4]=5;
    
    x[1][0]=6;
    x[1][1]=7;
    x[1][2]=8;
    x[1][3]=9;
    x[1][4]=10;
    
    x[2][0]=11;
    x[2][1]=12;
    x[2][2]=13;
    x[2][3]=14;
    x[2][4]=15;
    
    x[3][0]=16;
    x[3][1]=17;
    x[3][2]=18;
    x[3][3]=19;
    x[3][4]=20;

    y[0][0]=10;
    y[0][1]=20;

    y[1][0]=30;
    y[1][1]=40;

    y[2][0]=50;
    y[2][1]=60;

    y[3][0]=70;
    y[3][1]=80;

    y[4][0]=90;
    y[4][1]=100;

    z=multiply_matrix(x,4,5,y,5,2,&r,&c);
    if(z==NULL)
    {
        printf("Low Memory...\n");
        destroy_matrix(x,4,5);
        destroy_matrix(y,5,2);
        return 0;
    }
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            printf("%8d ",z[i][j]);
        }
        printf("\n");
    }
    destroy_matrix(x,4,5);
    destroy_matrix(y,5,2);
    destroy_matrix(z,r,c);
    return 0;
}
