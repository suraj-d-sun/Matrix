//Cropping
//Vertical Flip
//Horizontal Flip

#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

#define SUCCEEDED 1
#define FAILED 0

typedef struct {
    long unsigned int width;
    long unsigned int height;
    int channels;
    unsigned char **data;
    J_COLOR_SPACE color_space;
} raw_jpeg;

// Function Prototypes
void write_jpeg(raw_jpeg *raw, const char *file_name, int *success);
raw_jpeg *read_jpeg(const char *file_name);
void release_raw_jpeg(raw_jpeg *raw);
void color2gray_jpeg(raw_jpeg *raw);
raw_jpeg *vertical_flip_jpeg(raw_jpeg *raw);

int main(int argc, char *argv[]) {
    char *source_file, *target_file;
    int success = 0;
    raw_jpeg *raw, *new_raw;

    if (argc != 3) {
        printf("Usage: %s source_file.jpg target_file.jpg\n", argv[0]);
        return 0;
    }

    source_file = argv[1];
    target_file = argv[2];

    raw = read_jpeg(source_file);
    if (raw == NULL) {
        printf("Unable to read %s\n", source_file);
        return 0;
    }

    new_raw = vertical_flip_jpeg(raw);
    write_jpeg(new_raw, target_file, &success);
    if (!success) {
        printf("Unable to create %s\n", target_file);
    }

    release_raw_jpeg(raw);
    release_raw_jpeg(new_raw);

    printf("END!\n");
    return 0;
}

void write_jpeg(raw_jpeg *raw, const char *file_name, int *success) {
    int i;
    FILE *f;
    struct jpeg_compress_struct jpeg;
    struct jpeg_error_mgr error_manager;

    if (success)
        *success = FAILED;

    if (file_name == NULL)
        return;

    f = fopen(file_name, "wb");
    if (f == NULL)
        return;

    jpeg.err = jpeg_std_error(&error_manager);
    jpeg_create_compress(&jpeg);
    jpeg_stdio_dest(&jpeg, f);

    jpeg.image_width = raw->width;
    jpeg.image_height = raw->height;
    jpeg.input_components = raw->channels;
    jpeg.in_color_space = raw->color_space;

    jpeg_set_defaults(&jpeg);
    jpeg_set_quality(&jpeg, 100, TRUE);
    jpeg_start_compress(&jpeg, TRUE);

    i = 0;
    while (jpeg.next_scanline < raw->height) {
        jpeg_write_scanlines(&jpeg, &(raw->data[i]), 1);
        i++;
    }

    jpeg_finish_compress(&jpeg);
    jpeg_destroy_compress(&jpeg);

    if (success)
        *success = SUCCEEDED;

    fclose(f);
}

raw_jpeg *read_jpeg(const char *file_name) {
    FILE *f;
    unsigned char **data;
    struct jpeg_decompress_struct jpeg;
    struct jpeg_error_mgr error_manager;
    long unsigned int width, height;
    int channels, i, j;
    raw_jpeg *raw;
    J_COLOR_SPACE color_space;

    if (file_name == NULL)
        return NULL;

    f = fopen(file_name, "rb");
    if (f == NULL)
        return NULL;

    jpeg.err = jpeg_std_error(&error_manager);
    jpeg_create_decompress(&jpeg);
    jpeg_stdio_src(&jpeg, f);
    jpeg_read_header(&jpeg, TRUE);
    jpeg_start_decompress(&jpeg);

    width = jpeg.output_width;
    height = jpeg.output_height;
    channels = jpeg.num_components;
    color_space = jpeg.out_color_space;

    data = (unsigned char **)malloc(sizeof(unsigned char *) * height);
    if (data == NULL)
        return NULL;

    for (i = 0; i < height; i++) {
        data[i] = (unsigned char *)malloc(sizeof(unsigned char) * width * channels);
        if (data[i] == NULL) {
            for (j = 0; j < i; j++)
                free(data[j]);
            free(data);
            return NULL;
        }
    }

    i = 0;
    while (jpeg.output_scanline < height) {
        jpeg_read_scanlines(&jpeg, &data[i], 1);
        i++;
    }

    jpeg_finish_decompress(&jpeg);
    jpeg_destroy_decompress(&jpeg);
    fclose(f);

    raw = (raw_jpeg *)malloc(sizeof(raw_jpeg));
    if (raw == NULL) {
        for (i = 0; i < height; i++)
            free(data[i]);
        free(data);
        return NULL;
    }

    raw->width = width;
    raw->height = height;
    raw->channels = channels;
    raw->color_space = color_space;
    raw->data = data;

    return raw;
}

void release_raw_jpeg(raw_jpeg *raw) {
    int i;
    if (!raw)
        return;
    if (raw->data == NULL) {
        free(raw);
        return;
    }
    for (i = 0; i < raw->height; i++) {
        if (raw->data[i] != NULL)
            free(raw->data[i]);
    }
    free(raw->data);
    free(raw);
}

void color2gray_jpeg(raw_jpeg *raw) {
    unsigned char r, g, b, nc;
    int h, w;
    if (!raw || raw->data == NULL)
        return;
    for (h = 0; h < raw->height; h++) {
        for (w = 0; w < raw->width; w++) {
            r = raw->data[h][w * 3 + 0];
            g = raw->data[h][w * 3 + 1];
            b = raw->data[h][w * 3 + 2];
            nc = (r + g + b) / 3;
            raw->data[h][w * 3 + 0] = nc;
            raw->data[h][w * 3 + 1] = nc;
            raw->data[h][w * 3 + 2] = nc;
        }
    }
}

raw_jpeg *vertical_flip_jpeg(raw_jpeg *raw) {
    if (raw == NULL)
        return NULL;

    raw_jpeg *vertical_flip;
    vertical_flip = (raw_jpeg *)malloc(sizeof(raw_jpeg));
    if (vertical_flip == NULL)
        return NULL;

    unsigned char **flipped_image = (unsigned char **)malloc(sizeof(unsigned char *) * (raw->height));
    if (flipped_image == NULL)
        return NULL
