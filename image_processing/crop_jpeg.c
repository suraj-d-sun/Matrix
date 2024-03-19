#include <jpeg.h>
// #include<kernels.h>
#include <matrix.h>
#include <string.h>

raw_jpeg *crop_jpeg(raw_jpeg *raw, int center_x, int center_y, int width, int height, int *success)
{
    int start_x, start_y, end_x, end_y;
    raw_jpeg *new_raw;
    int y;
    if (success)
        *success = 0;
    start_x = (center_x - (width / 2));
    if (start_x < 0)
        start_x = 0;
    start_y = (center_y - (height / 2));
    if (start_y < 0)
        start_y = 0;
    end_x = center_x + (width / 2);
    if (end_x >= raw->width)
        end_x = raw->width - 1;
    end_y = center_y + (height / 2);
    if (end_y >= raw->height)
        end_y = raw->height - 1;
    width = end_x - start_x + 1;
    height = end_y - start_y + 1;

    new_raw = (raw_jpeg *)malloc(sizeof(raw_jpeg));

    if (new_raw == NULL)
        return NULL;

    new_raw->data = create_matrix_uchar(height, width * 3);
    if (new_raw->data == NULL)
    {    
    free(new_raw);
    return NULL;
    }
    new_raw->width = width;
    new_raw->height = height;
    new_raw->color_space = raw->color_space;
    new_raw->channels = raw->channels;
    for (y = 0; y < height; ++y)
    {
        memcpy(new_raw->data[y],raw->data[y+start_y]+(start_x*3),width*3);
    }
    if(success) *success=1;
    return new_raw;
}

int main(int argc, char *argv[])
{
    char *source_file, *target_file;
    int center_x,center_y;
    int width,height;
    int success ;
    raw_jpeg *raw;
    raw_jpeg *new_raw;
    int matrix_dimension;
    if (argc != 7)
    {
        printf("Usage [./crop_jpeg source_file.jpg target_file.jpg center_x center_y width height]\n");
        return 0;
    }
    source_file = argv[1];
    target_file = argv[2];
    center_x= atoi(argv[3]);
    center_y= atoi(argv[4]);
    width=atoi(argv[5]);
    height=atoi(argv[6]);
    raw = read_jpeg(source_file);
    if (raw == NULL)
    {
        printf("Unable to read %s\n", source_file);
        return 0;
    }
    new_raw=crop_jpeg(raw,center_x,center_y,width,height,&success);
    if(!success)
    {
        printf("Low Memory\n");
        return 0;
    }
    write_jpeg(raw, target_file, &success);
    if (!success)
    {
        printf("Unable to create %s\n", target_file);
    }
    release_raw_jpeg(raw);
    release_raw_jpeg(new_raw);
    return 0;
}
