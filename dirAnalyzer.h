#ifndef ANALIZER_DIRANALYZER_H
#define ANALIZER_DIRANALYZER_H

#include <list>
#include <string>
#include <vector>
#include "mainStructure.h"

namespace dirAnalyzer {
    using namespace std;

    list <string> *getList(const char *dirName, const char *filter = ".log");

    vector<string> *getSubDirs(const char *dirName);

    void analyze(const char *name, int numControls);

}
#endif //ANALIZER_DIRANALYZER_H
