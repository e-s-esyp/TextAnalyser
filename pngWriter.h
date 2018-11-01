#ifndef ANALIZER_PNGWRITER_H
#define ANALIZER_PNGWRITER_H

int writePNG(const char *fileName, unsigned int width, unsigned int height, unsigned char **imageData,
             const char *title);

namespace pngWriter {
    void test();
}
#endif //ANALIZER_PNGWRITER_H
