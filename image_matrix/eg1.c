//code to load the .jpg file and get its height and width
#include <stdio.h> // this should be above jconfig and jpeglib
#include <jconfig.h>
#include <jpeglib.h>
int main(int c, char *v[])
{
    FILE *f;
    struct jpeg_decompress_struct jpeg;
    struct jpeg_error_mgr error_manager;
    f = fopen(v[1], "rb"); // b for binary mode
    long unsigned int width;
    long unsigned int height;

    if (f == NULL)
    {
        printf("%s not found\n", v[1]);
        return 0;
    }

    jpeg.err = jpeg_std_error(&error_manager);
    jpeg_create_decompress(&jpeg);
    jpeg_stdio_src(&jpeg, f);
    jpeg_read_header(&jpeg, TRUE);
    jpeg_start_decompress(&jpeg);

    width = jpeg.output_width;
    height = jpeg.output_height;
    printf("width: %lu Height: %lu\n", width, height);

    return 0;
}