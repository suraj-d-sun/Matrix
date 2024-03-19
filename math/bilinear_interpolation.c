#include <matrix.h>
#include <stdlib.h>
#include <math.h>

double **interpolate_bilinear(int **x, int rows, int cols, int new_rows, int new_cols)
{
    double **y;
    int x_axis_lower_index, x_axis_upper_index;
    int y_axis_lower_index, y_axis_upper_index;
    double x_ratio;
    double y_ratio;
    double x_weight;
    double y_weight;
    double d1, d2, d3, d4;
    double M, U, T;
    int x_axis, y_axis;
    int k1, k2;

    y = create_matrix_double(new_rows, new_cols);
    if (y == NULL) return NULL;
    x_ratio = (((double)cols) - 1.0) / (((double)new_cols) - 1.0);
    y_ratio = (((double)rows) - 1.0) / (((double)new_rows) - 1.0);
    for (y_axis = 0; y_axis < new_rows; ++y_axis)
    {
        for (x_axis = 0; x_axis < new_cols; ++x_axis)
        {
            k1 = y_axis;
            y_axis_lower_index = floor(y_ratio * k1);
            y_axis_upper_index = ceil(y_ratio * k1);

            k2 = x_axis;
            x_axis_lower_index = floor(x_ratio * k2);
            x_axis_upper_index = ceil(x_ratio * k2);

            y_weight = (y_ratio * k1) - y_axis_lower_index;
            x_weight = (x_ratio * k2) - x_axis_lower_index;

            d1 = (double)x[y_axis_lower_index][x_axis_lower_index];
            d2 = (double)x[y_axis_lower_index][x_axis_upper_index];

            d3 = (double)x[y_axis_upper_index][x_axis_lower_index];
            d4 = (double)x[y_axis_upper_index][x_axis_upper_index];

            M = d1 * (1.0 - x_weight) + (d2 * x_weight);
            U = d3 * (1.0 - x_weight) + (d4 * x_weight);
            T = M * (1.0 - y_weight) + (U * y_weight);

            y[y_axis][x_axis] = T;
        }
    }
    return y;
}

int main()
{
    int r1[] = {10, 20, 30, 40, 50, 60};
    int r2[] = {70, 80, 90, 100, 110, 120};
    int r3[] = {130, 140, 150, 160, 170, 180};
    int r4[] = {190, 200, 210, 220, 230, 240};
    int r5[] = {250, 260, 270, 280, 290, 300};
    int *x[] = {r1, r2, r3, r4, r5};

    int r, c;
    double **y = interpolate_bilinear(x, 5, 6, 3, 10);  //3 & 10 can be anything
    if (y == NULL)
    {
        printf("Cannot Scale\n");
        return 0;
    }
    for (r = 0; r < 3; r++)
    {
        for (c = 0; c < 10; c++)
        {
            printf("%lf ", y[r][c]);
        }
        printf("\n");
    }
    destroy_matrix((void **)y,3,10);
    return 0;
}