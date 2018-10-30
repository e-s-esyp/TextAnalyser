#include <iostream>
#include <map>
#include "logger.h"
#include "dirAnalyzer.h"

#ifndef __e2k__

#include "pngWriter.h"
#include "mandelbrotWriter.h"

#endif
using namespace std;

class arguments {
public:
    map<string, string> assigns;
    bool error = false;

    arguments(int argc, char **argv) {
        for (int i = 1; i < argc; i++) {
            string s(argv[i]);
            if (s.length() < 3 || s[0] != '-') {
                error = true;
                return;
            }
            unsigned long p = s.find('=');
            if (p != string::npos) {
                assigns[s.substr(1, p - 1)] = s.substr(p + 1, string::npos);
            } else {
                error = true;
                return;
            }
        }
    }

    void printDefault() {
        logger::put("Analyzer options:\n");
        logger::put("-j=<num threads>\n");
        logger::put("-maindir=<dir name, where subdirs will be analyzed>\n");
        logger::put("-dir=<dir name, where .log files will be analyzed>\n");
    }

    void runAnalizer() {
        if (error) {
            printDefault();
            return;
        }
        int numThreads = 1;
        if (assigns.find("j") != assigns.end()) {
            numThreads = stoi(assigns["j"]);
            assigns.erase("j");
        }
        logger::put("Number of used threads at one time = %d\n", numThreads);
        string mainDir(".");
        if (assigns.find("maindir") != assigns.end()) {
            mainDir = assigns["maindir"];
            assigns.erase("maindir");
        }
        bool allDirs = true;
        string dir;
        if (assigns.find("dir") != assigns.end()) {
            dir = assigns["dir"];
            allDirs = false;
            assigns.erase("dir");
        }
        if (!assigns.empty()) {
            printDefault();
            return;
        }
        if (allDirs) {
            logger::put("Processing all subdirs:\n");
            auto subDirs = dirAnalyzer::getSubDirs(mainDir.data());
            int i = 0;
            for (const auto &subdir:*subDirs) {
                logger::put("%2d %s\n", i++, subdir.data());
            }
            unsigned long numFiles = 0;
            for (const auto &subdir:*subDirs) {
                numFiles += dirAnalyzer::analyze(subdir.data(), numThreads);
            }
            logger::putTimed("Total number of files = %d", numFiles);
            delete subDirs;
        } else {
            dirAnalyzer::analyze(dir.data(), numThreads);
        }
    }
};

#ifdef __e2k__
void function1(int argc, char **argv) {
    logger::putTimed("Starting. WARNING: max file size %d byte", MAX_BUF_SIZE);
    arguments args(argc, argv);
    args.runAnalizer();
}
#else

void function1(int argc, char **argv) {
    auto a = string("a.png");
    const char *argv2[2];
    argv2[0] = argv[0];
    argv2[1] = a.data();
    write_png_file(2, &argv2[0]);
}

void function2() {
    auto fileName("image.png");
    unsigned int width = 512;
    unsigned int height = 512;
    unsigned char *imageData[height];
    auto title("title");
    for (int i = 0; i < height; ++i) {
        imageData[i] = new unsigned char[width * 3];
        for (int j = 0; j < width * 3; ++j) {
            imageData[i][j] = static_cast<unsigned char>(i + j);
        }
    };
    writePNG(fileName, width, height, imageData, title);
}

#endif

int main(int argc, char **argv) {
//    function1(argc, argv);
    function2();
    return 0;
}