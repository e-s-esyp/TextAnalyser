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
    unsigned int height;
    unsigned int width;
    unsigned char **imageData;
    long maxLevel = 0;

    void parse();

    void analyze();

public:
    explicit fileAnalyzer(const string &fullName, unsigned int height, unsigned int width) {
        data = nullptr;
        name.assign(fullName);
        fileAnalyzer::height = height;
        fileAnalyzer::width = width;
        finished = false;
        fileSize = 0;
        imageData = new unsigned char *[height];
        for (int i = 0; i < height; ++i) {
            imageData[i] = new unsigned char[width * 3];
            for (int j = 0; j < width * 3; ++j) {
                imageData[i][j] = 254;
            }
        }
    }

    ~fileAnalyzer() {
        for (int i = 0; i < height; ++i) {
            delete[] imageData[i];
        };
        delete[] imageData;
    }

    void perform();

    string getReport();

    string getName();

    long getFileSize();

    bool isFinished();

    void writeFigure();

    void setMinMax();

    void drawFigure(unsigned char **picture, int figureIndex);
};

#endif //ANALIZER_PARSER_H
