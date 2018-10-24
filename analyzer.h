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
    thread executor;

    void parse();

    void analyze();

public:
    explicit fileAnalyzer(const string &fullName) {
        name.assign(fullName);
    }

    void perform();

    void performInThread();

    string getReport();

    friend void theFunction(fileAnalyzer *a);
};

#endif //ANALIZER_PARSER_H
