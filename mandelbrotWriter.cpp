#include "mandelbrotWriter.h"
// LibPNG example
// A.Greensted
// http://www.labbookpages.co.uk

// Version 2.0
// With some minor corrections to Mandlebrot code (thanks to Jan-Oliver)

// Version 1.0 - Initial release

#include <cmath>
#include <png.h>
#include <string>

// Creates a test image for saving. Creates a Mandelbrot Set fractal of size width x height
float *createMandelbrotImage(int width, int height, float xS, float yS, float rad, int maxIteration);

// This takes the float value 'val', converts it to red, green & blue values, then
// sets those values into the image memory buffer location pointed to by 'ptr'
inline void setRGB(png_byte *ptr, float val);

// This function actually writes out the PNG image file. The string 'title' is
// also written into the image file
int writeImage(const char *filename, int width, int height, float *buffer, char *title);

int write_png_file(int argc, const char *argv[]) {
    // Make sure that the output filename argument has been provided
    if (argc != 2) {
        fprintf(stderr, "Please specify output file\n");
        return 1;
    }

    // Specify an output image size
    int width = 4000;
    int height = 4000;

    // Create a test image - in this case a Mandelbrot Set fractal
    // The output is a 1D array of floats, length: width * height
    printf("Creating Image\n");
    float *buffer = createMandelbrotImage(width, height, -0.802f, -0.177f, 0.011, 110);
    if (buffer == nullptr) {
        return 1;
    }

    // Save the image to a PNG file
    // The 'title' string is stored as part of the PNG file
    printf("Saving PNG\n");
    int result = writeImage(argv[1], width, height, buffer, "This is my test image");

    // Free up the memorty used to store the image
    free(buffer);

    return result;
}

inline void setRGB(png_byte *ptr, float val) {
    auto v = (int) (val * 767);
    if (v < 0) v = 0;
    if (v > 767) v = 767;
    auto offset = (unsigned char) (v % 256);

    if (v < 256) {
        ptr[0] = 0;
        ptr[1] = 0;
        ptr[2] = offset;
    } else if (v < 512) {
        ptr[0] = 0;
        ptr[1] = offset;
        ptr[2] = (unsigned char) 255 - offset;
    } else {
        ptr[0] = offset;
        ptr[1] = (unsigned char) 255 - offset;
        ptr[2] = 0;
    }
}

int writeImage(const char *filename, int width, int height, float *buffer, char *title) {
    int code = 0;
    FILE *fp = nullptr;
    png_structp png_ptr = nullptr;
    png_infop info_ptr = nullptr;
    png_bytep row = nullptr;

    // Open file for writing (binary mode)
    fp = fopen(filename, "wb");
    if (fp == nullptr) {
        fprintf(stderr, "Could not open file %s for writing\n", filename);
        code = 1;
        goto finalise;
    }

    // Initialize write structure
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (png_ptr == nullptr) {
        fprintf(stderr, "Could not allocate write struct\n");
        code = 1;
        goto finalise;
    }

    // Initialize info structure
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == nullptr) {
        fprintf(stderr, "Could not allocate info struct\n");
        code = 1;
        goto finalise;
    }

    // Setup Exception handling
    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, "Error during png creation\n");
        code = 1;
        goto finalise;
    }

    png_init_io(png_ptr, fp);

    // Write header (8 bit colour depth)
    png_set_IHDR(png_ptr, info_ptr, width, height,
                 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    // Set title
    if (title != nullptr) {
        png_text title_text{PNG_TEXT_COMPRESSION_NONE, "Title", title};
        png_set_text(png_ptr, info_ptr, &title_text, 1);
    }

    png_write_info(png_ptr, info_ptr);

    // Allocate memory for one row (3 bytes per pixel - RGB)
    row = (png_bytep) malloc(3 * width * sizeof(png_byte));

    // Write image data
    int x, y;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            setRGB(&(row[x * 3]), buffer[y * width + x]);
        }
        png_write_row(png_ptr, row);
    }

    // End write
    png_write_end(png_ptr, nullptr);

    finalise:
    if (fp != nullptr) fclose(fp);
    if (info_ptr != nullptr) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    if (png_ptr != nullptr) png_destroy_write_struct(&png_ptr, (png_infopp) nullptr);
    if (row != nullptr) free(row);

    return code;
}

float *createMandelbrotImage(int width, int height, float xS, float yS, float rad, int maxIteration) {
    float *buffer = (float *) malloc(width * height * sizeof(float));
    if (buffer == nullptr) {
        fprintf(stderr, "Could not create image buffer\n");
        return nullptr;
    }

    // Create Mandelbrot set image

    int xPos, yPos;
    float minMu = maxIteration;
    float maxMu = 0;

    for (yPos = 0; yPos < height; yPos++) {
        float yP = (yS - rad) + (2.0f * rad / height) * yPos;

        for (xPos = 0; xPos < width; xPos++) {
            float xP = (xS - rad) + (2.0f * rad / width) * xPos;

            int iteration = 0;
            float x = 0;
            float y = 0;

            while (x * x + y * y <= 4 && iteration < maxIteration) {
                float tmp = x * x - y * y + xP;
                y = 2 * x * y + yP;
                x = tmp;
                iteration++;
            }

            if (iteration < maxIteration) {
                float modZ = sqrt(x * x + y * y);
                float mu = iteration - (log(log(modZ))) / log(2);
                if (mu > maxMu) maxMu = mu;
                if (mu < minMu) minMu = mu;
                buffer[yPos * width + xPos] = mu;
            } else {
                buffer[yPos * width + xPos] = 0;
            }
        }
    }

    // Scale buffer values between 0 and 1
    int count = width * height;
    while (count) {
        count--;
        buffer[count] = (buffer[count] - minMu) / (maxMu - minMu);
    }

    return buffer;
}
