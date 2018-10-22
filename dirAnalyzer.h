#ifndef ANALIZER_DIRANALYZER_H
#define ANALIZER_DIRANALYZER_H

#include <list>
#include <string>

namespace dirAnalyzer {
    using namespace std;

    list <string> *getList(const char *dirName, const char *filter = ".log");
}
#endif //ANALIZER_DIRANALYZER_H
