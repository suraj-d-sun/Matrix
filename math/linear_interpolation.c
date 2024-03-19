#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double *linear_interpolate(int *x, int x_size, int new_size)
{
    double *y;
    double ratio;
    int lower_index, upper_index;
    double d1, d2;
    double weight;
    double value;
    int k;

    y = (double *)malloc(sizeof(double) * new_size);
    if (y == NULL) return NULL;
    ratio = ((double)(x_size - 1)) / ((double)(new_size - 1));

    for (k = 0; k < new_size; ++k)
    {
        lower_index = floor(ratio * k);
        upper_index = ceil(ratio * k);
        d1 = (double)x[lower_index];
        d2 = (double)x[upper_index];
        weight = (ratio * k) - lower_index;
        value = d1 * (1.0 - weight) + d2 * weight;
        y[k] = value;
    }
    return y;
}

int main()
{
    int x[5]={10,20,30,40,50};
    double *y;
    int i;
    y = linear_interpolate(x, 5, 4);
    if(y==NULL)
    {
        printf("Unable to scale\n");
        return 0;
    }
    for(i=0;i<4;i++) printf("%lf\n",y[i]);
    free(y);
    return 0;
}