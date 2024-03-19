#include <jpeg.h>
#include <kernels.h>
#include <matrix.h>
raw_jpeg *flip_horizontal_jpeg(raw_jpeg *raw, int *success)
{
    raw_jpeg *new_raw;
    int new_x;
    int x, y;
    if (success) *success = 0;
    if (!raw) return NULL;
    new_raw = create_new_raw_jpeg(raw->width, raw->height, raw->channels, raw->color_space);
    if (new_raw == NULL) return NULL;

    for (y = 0; y < raw->height; ++y)
    {
        for (new_x = 0, x = raw->width - 1; x >= 0; --x, ++new_x)
        {
            new_raw->data[y][new_x * 3 + 0] = raw->data[y][x * 3 + 0];
            new_raw->data[y][new_x * 3 + 1] = raw->data[y][x * 3 + 1];
            new_raw->data[y][new_x * 3 + 2] = raw->data[y][x * 3 + 2];
        }
    }
    if(success) *success=1;
    return new_raw;
}


int main(int argc, char *argv[])
{
    char *source_file, *target_file;
    int success ;
    raw_jpeg *raw;
    raw_jpeg *new_raw;
    if (argc != 3)
    {
        printf("Usage [./flip_horizontal source_file.jpg target_file.jpg]\n");
        return 0;
    }
    source_file = argv[1];
    target_file = argv[2];
    raw = read_jpeg(source_file);
    if (raw == NULL)
    {
        printf("Unable to read %s\n", source_file);
        return 0;
    }
    new_raw=flip_horizontal_jpeg(raw,&success);
    if(!success)
    {
        printf("Low Memory\n");
        return 0;
    }
    write_jpeg(new_raw, target_file, &success);
    if (!success)
    {
        printf("Unable to create %s\n", target_file);
    }
    release_raw_jpeg(raw);
    release_raw_jpeg(new_raw);
    return 0;
}


