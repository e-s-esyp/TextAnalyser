#ifndef ANALIZER_PARSER_H
#define ANALIZER_PARSER_H

#include "mainStructure.h"
#include "stringLogger.h"
#include <list>
#include <thread>

using namespace std;

class fileAnalyzer {

protected:
    string name{};
    stringLogger report;
    list<S> *data;
    bool finished;
    long fileSize;
    S min{};
    S max{};
    const unsigned int width = 1024;
    const unsigned int height = 256;
    unsigned char **imageData;

    void parse();

    void analyze();

public:
    explicit fileAnalyzer(const string &fullName) {
        data = nullptr;
        name.assign(fullName);
        finished = false;
        fileSize = 0;
        imageData = new unsigned char *[height];
        for (int i = 0; i < height; ++i) {
            imageData[i] = new unsigned char[width * 3];
            for (int j = 0; j < width * 3; ++j) {
                imageData[i][j] = 240;
            }
        };

    }

    ~fileAnalyzer() {
        for (int i = 0; i < height; ++i) {
            delete [] imageData[i];
        };
        delete imageData;
    }

    void perform();

    string getReport();

    string getName();

    long getFileSize();

    bool isFinished();

    void writeFigure();

    void setMinMax();
};

#endif //ANALIZER_PARSER_H
