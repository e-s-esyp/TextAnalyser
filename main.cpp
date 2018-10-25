#include "logger.h"
#include "dirAnalyzer.h"
#include "analyzer.h"

using namespace std;

int main(int argc, char **argv) {
    logger::putTimed("Starting. WARNING: max file size %d byte", MAX_BUF_SIZE);
    auto dirName = (argc == 2) ? argv[1] : ".";
    auto dir = dirAnalyzer::getList(dirName);
    dir->sort();
    logger::putTimed("Have a dirList:");
    list<fileAnalyzer> analyzer;
    for (const auto &file:*dir) {
        logger::put(file.data());
        analyzer.emplace_back(file);
    }
    delete dir;
    //TODO: should make fixed number threads
    for (auto &file:analyzer) {
        file.performInThread();
//        file.perform();
    }
    for (auto &file:analyzer) {
        logger::put(file.getReport().data());
    }
    logger::putTimed("All done.");
    return 0;
}