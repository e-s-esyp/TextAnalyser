#ifndef ANALIZER_DIRANALYZER_H
#define ANALIZER_DIRANALYZER_H

#include <list>
#include <string>
#include "mainStructure.h"

namespace dirAnalyzer {
    using namespace std;

    list <string> *getList(const char *dirName, const char *filter = ".log");

    void analyze(const char *name);

}
#endif //ANALIZER_DIRANALYZER_H
