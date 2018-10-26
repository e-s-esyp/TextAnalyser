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
    list<S> *data = nullptr;
    bool finished;
    long fileSize;

    void parse();

    void analyze();

public:
    explicit fileAnalyzer(const string &fullName) {
        name.assign(fullName);
        finished = false;
        fileSize = 0;
    }

    void perform();

    string getReport();

    string getName();

    long getFileSize();

    bool isFinished();
};

#endif //ANALIZER_PARSER_H
