#include <iostream>
#include "logger.h"
#include "dirAnalyzer.h"
#include "analyzer.h"

using namespace std;

int main(int argc, char **argv) {
    logger::put("Starting. WARNING: max file size %d byte", MAX_BUF_SIZE);
    auto dirName = (argc == 2) ? argv[1] : ".";
    auto dir = dirAnalyzer::getList(dirName);
    dir->sort();
    logger::put("Have a dirList");
    list<fileAnalyzer> analyzer;
    for (const auto &file:*dir) {
        analyzer.emplace_back(file);
    }
    delete dir;
    for (auto &file:analyzer) {
        file.performInThread();
//        file.perform();
    }
    for (auto &file:analyzer) {
        cout << file.getReport();
    }
    logger::put("All done.");
    return 0;
}