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
    void parse();

    void analyze();

public:
    explicit fileAnalyzer(const string &fullName) {
        name.assign(fullName);
        finished = false;
    }

    void perform();

    string getReport();

    string getName();

    bool isFinished();
};

#endif //ANALIZER_PARSER_H
