#include <cstdio>
#include <png.h>
#include "pngWriter.h"
#include "myStrings.cpp"

int writePNG(const char *fileName, unsigned int width, unsigned int height, unsigned char **imageData,
             const char *title) {
    int code = 0;
    FILE *fp = nullptr;
    png_structp png_ptr = nullptr;
    png_infop info_ptr = nullptr;
    // Open file for writing (binary mode)
    fp = fopen(fileName, "wb");
    if (fp == nullptr) {
        fprintf(stderr, "Could not open file %s for writing\n", fileName);
        code = 1;
        goto finalise;
    }
    // Initialize write structure
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (png_ptr == nullptr) {
        fprintf(stderr, "Could not allocate write struct\n");
        code = 2;
        goto finalise;
    }
    // Initialize info structure
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == nullptr) {
        fprintf(stderr, "Could not allocate info struct\n");
        code = 3;
        goto finalise;
    }
    // Setup Exception handling
    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, "Error during png creation\n");
        code = 4;
        goto finalise;
    }
    png_init_io(png_ptr, fp);
    // Write header (8 bit colour depth)
    png_set_IHDR(png_ptr, info_ptr, width, height,
                 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    // Set title
    if (title != nullptr) {
        auto titleLength = strlen(title);
        char title_[titleLength];
        myStrings::copy0(title_, title, titleLength);
        auto Title = const_cast<char *>("Title");
        png_text title_text{PNG_TEXT_COMPRESSION_NONE, Title, title_};
        png_set_text(png_ptr, info_ptr, &title_text, 1);
    }
    png_write_info(png_ptr, info_ptr);
    png_write_image(png_ptr, imageData);
    png_write_end(png_ptr, nullptr);
    finalise:
    if (fp != nullptr) fclose(fp);
    if (info_ptr != nullptr) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    if (png_ptr != nullptr) png_destroy_write_struct(&png_ptr, (png_infopp) nullptr);
    return code;
}

