#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

#define SUCCEEDED 1
#define FAILED 0

typedef struct __raw_jpeg
{
    long unsigned int width;
    long unsigned int height;
    int channels;
    unsigned char **data;
    J_COLOR_SPACE color_space;
} raw_jpeg;

unsigned char **create_matrix_uchar(int rows, int cols);

raw_jpeg * create_new_raw_jpeg(int width,int height,int channels,J_COLOR_SPACE color_space)
{
    raw_jpeg *new_raw;
    new_raw=(raw_jpeg *)malloc(sizeof(raw_jpeg));
    if(!new_raw) return NULL;
    new_raw->data=create_matrix_uchar(height,width*channels);
    if(new_raw->data==NULL)
    {
        free(new_raw);
        return NULL;
    }
    new_raw->width=width;
    new_raw->height=height;
    new_raw->channels=channels;
    new_raw->color_space=color_space;
    return new_raw;
}

void write_jpeg(raw_jpeg *raw, const char *file_name, int *success)
{
    int i;
    FILE *f;
    struct jpeg_compress_struct jpeg;
    struct jpeg_error_mgr error_manager;
    if (success) *success = FAILED; 
    if (file_name == NULL) return;
    f = fopen(file_name, "wb");
    if (f == NULL) return;
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
    while (jpeg.next_scanline < raw->height)
    {
        jpeg_write_scanlines(&jpeg, &(raw->data[i]), 1);
        i++;
    }
    jpeg_finish_compress(&jpeg);
    jpeg_destroy_compress(&jpeg);
    if (success) *success = SUCCEEDED;
    fclose(f);
}

raw_jpeg *read_jpeg(const char *file_name)
{
    FILE *f;
    unsigned char **data;
    struct jpeg_decompress_struct jpeg;
    struct jpeg_error_mgr error_manager;
    long unsigned int width;
    long unsigned int height;
    int channels;
    int i, j;
    raw_jpeg *raw;
    J_COLOR_SPACE color_space;
    if (file_name == NULL) return NULL;
    f = fopen(file_name, "rb");
    if (f == NULL) return NULL;
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
    if (data == NULL) return NULL;

    for (i = 0; i < height; i++)
    {
        data[i] = (unsigned char *)malloc(sizeof(unsigned char) * width * channels);
        if (data[i] == NULL)
        {
            for (j = 0; j < i; j++)
                free(data[j]);
            free(data);
            return NULL;
        }
    }
    i = 0;
    while (jpeg.output_scanline < height)
    {
        jpeg_read_scanlines(&jpeg, &data[i], 1);
        i++;
    }

    jpeg_finish_decompress(&jpeg);
    jpeg_destroy_decompress(&jpeg);
    fclose(f);

    raw = (raw_jpeg *)malloc(sizeof(raw_jpeg));
    if (raw == NULL)
    {
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

void release_raw_jpeg(raw_jpeg *raw)
{
    int i;
    if (!raw) return;
    if (raw->data == NULL)
    {
        free(raw);
        return;
    }
    for (i = 0; i < raw->height; i++)
    {
        if (raw->data[i] != NULL) free(raw->data[i]);
    }
    free(raw->data);
    free(raw);
}

void color2gray_jpeg(raw_jpeg *raw)
{
    unsigned char r, g, b, nc;
    int h, w;
    if (!raw || raw->data == NULL) return;
    for (h = 0; h < raw->height; h++)
    {
        for (w = 0; w < raw->width; w++)
        {
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

void apply_box_blur_jpeg_to_cell(raw_jpeg *raw, int row, int col, int matrix_dimension)
{
    int start_row;
    int end_row;
    int start_col;
    int end_col;
    int offset;
    int height;
    int width;
    int r, c;
    int er, ec;
    int r_sum, g_sum, b_sum;
    int r_sum_avg, g_sum_avg, b_sum_avg;
    unsigned char red, green, blue;
    int divide_by = matrix_dimension * matrix_dimension;
    height = raw->height;
    width = raw->width;
    offset = matrix_dimension / 2;
    start_row = row - offset;
    start_col = col - offset;
    end_row = row + offset;
    end_col = col + offset;
    r_sum = g_sum = b_sum = 0;
    for (r = start_row; r <= end_row; ++r)
    {
        for (c = start_col; c <= end_col; ++c)
        {
            if (r < 0)
            {
                er = 0;
            }else if (r >= height)
            {
                er = height - 1;
            }
            else
            {
                er = r;
            }
            if (c < 0)
            {
                ec = 0;
            }else if (c >= width)
            {
                ec = width - 1;
            }
            else
            {
                ec = c;
            }
            r_sum += raw->data[er][ec * 3 + 0];
            g_sum += raw->data[er][ec * 3 + 1];
            b_sum += raw->data[er][ec * 3 + 2];
        }
    }
    r_sum_avg = r_sum / divide_by;
    g_sum_avg = g_sum / divide_by;
    b_sum_avg = b_sum / divide_by;

    red = (unsigned char)r_sum_avg;
    green = (unsigned char)g_sum_avg;
    blue = (unsigned char)b_sum_avg;

    raw->data[row][col * 3 + 0] = red;
    raw->data[row][col * 3 + 1] = green;
    raw->data[row][col * 3 + 2] = blue;
}

void box_blur_jpeg(raw_jpeg *raw, int matrix_dimension)
{
    int width;
    int height;
    int row;
    int col;
    width=raw->width;
    height=raw->height;
    for(row=0;row<height;++row)
    {
        for(col=0;col<width;++col)
        {
            apply_box_blur_jpeg_to_cell(raw,row,col,matrix_dimension);
        }
    }
}

