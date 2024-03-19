#include<./jpeg.h>
int main(int argc, char *argv[])
{
    char *source_file, *target_file;
    int success ;
    raw_jpeg *raw;
    int matrix_dimension;
    if (argc != 4)
    {
        printf("Usage [./box_blur source_file.jpg target_file.jpg matrix_dimesion]\n");
        return 0;
    }
    source_file = argv[1];
    target_file = argv[2];
    matrix_dimension= atoi(argv[3]);
    raw = read_jpeg(source_file);
    if (raw == NULL)
    {
        printf("Unable to read %s\n", source_file);
        return 0;
    }
    box_blur_jpeg(raw,matrix_dimension);
    write_jpeg(raw, target_file, &success);
    if (!success)
    {
        printf("Unable to create %s\n", target_file);
    }
    release_raw_jpeg(raw);
    return 0;
}
