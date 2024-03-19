#include <matrix.h>
#include <jpeglib.h>
#include <stdlib.h>
#include <math.h>
#include <jpeg.h>
raw_jpeg * scale_jpeg_using_bilinear_interpolation(raw_jpeg *src, int new_width, int new_height, int *success)
{
    raw_jpeg *new_raw;
    unsigned char **y;
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
    int i;
    int cols=src->width;
    int rows=src->height;
    int new_rows=new_height;
    int new_cols=new_width;
    if(success) *success=0; //0 for false

    new_raw=(raw_jpeg *)malloc(sizeof(raw_jpeg));
    if(new_raw==NULL) return NULL;
    y = create_matrix_uchar(new_rows, new_cols*3); //beacuse of RGB, 3 value in each cell
    if (y == NULL)
    {
        free(new_raw);
        return NULL;
    }  
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

            for(i=0;i<=2;i++)
            {
                d1 = (double)src->data[y_axis_lower_index][x_axis_lower_index*3+i];
                d2 = (double)src->data[y_axis_lower_index][x_axis_upper_index*3+i];

                d3 = (double)src->data[y_axis_upper_index][x_axis_lower_index*3+i];
                d4 = (double)src->data[y_axis_upper_index][x_axis_upper_index*3+i];

                M = d1 * (1.0 - x_weight) + (d2 * x_weight);
                U = d3 * (1.0 - x_weight) + (d4 * x_weight);
                T = M * (1.0 - y_weight) + (U * y_weight);

                y[y_axis][x_axis*3+i] = (unsigned char)round(T);
            }
        }
    }
    new_raw->data=y;
    new_raw->width=new_width;
    new_raw->height=new_height;
    new_raw->channels=src->channels;
    new_raw->color_space=src->color_space;
    *success=1; //1 for true
    return new_raw;
}
int main(int argc, char *argv[])
{
    char *source_file, *target_file;
    raw_jpeg *new_raw;
    int success;
    int new_width,new_height;
    raw_jpeg *raw;
    if (argc != 5)
    {
        printf("Usage: [./scale_image_bilinear_interpolation source_file.jpg target_file.jpg width height]\n");
        return 0;
    }
    source_file = argv[1];
    target_file = argv[2];
    new_width=atoi(argv[3]);
    new_height=atoi(argv[4]);
    raw = read_jpeg(source_file);
    if (raw == NULL)
    {
        printf("Unable to read %s\n", source_file);
        return 0;
    }
    new_raw=scale_jpeg_using_bilinear_interpolation(raw,new_width,new_height,&success);
    if (!success)
    {
        printf("Low Memory\n");
        return 0;
    }
    write_jpeg(new_raw,target_file,&success);
    if(!success)
    {
        printf("Unable to create %s\n",target_file);
    }
    release_raw_jpeg(raw);
    release_raw_jpeg(new_raw);
    return 0;
}
