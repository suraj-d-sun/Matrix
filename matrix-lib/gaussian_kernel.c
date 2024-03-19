#include <matrix.h>
#include <math.h>

double get_gaussian_kernel_cell_value(int x, int y, double sigma)
{
    double pi = M_PI; // cos(M_PI) is -1 // acos(-1); //a cos for inverse
    double part_1 = (1.0 / (2.0 * pi * sigma * sigma));
    double part_2 = ((x * x) + (y * y)) / (2.0 * sigma * sigma);
    double value = part_1 * exp(-part_2);
    return value;
}

double ** create_gaussian_kernel(int kernel_size, double sigma)
{
    int x, y;
    double **kernel;
    int rows = kernel_size;
    int cols = kernel_size;
    int radius;
    int r, c;
    double value;
    double sum;
    if (kernel_size % 2 == 0) return NULL;
    radius = (kernel_size - 1) / 2;
    kernel = create_matrix_double(rows, cols);
    if (kernel == NULL) return NULL;
    x = -radius;
    y = -radius;
    sum = 0.0;
    for (r = 0; r < rows; ++r, ++y)
    {
        for (c = 0; c < cols; ++c, ++x)
        {
            value = get_gaussian_kernel_cell_value(x, y, sigma);
            sum += value;
            kernel[r][c] = value;
        }
    }
    for (r = 0; r < rows; ++r)
    {
        for (c = 0; c < cols; ++c)
        {
            kernel[r][c] /= sum;
        }
    }
    return kernel;
}

int main()
{
    double **m;
    int r, c;
    m = create_gaussian_kernel(5, 4); // 5x5 and sigma is 4
    for (r = 0; r <= 4; ++r)
    {
        for (c = 0; c <= 4; ++c)
        {
            printf("%lf ",m[r][c]);
        }
        printf("\n");
    }
    destroy_matrix((void **)m,5,5);
    return 0;
}