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
    for (const auto &file:*dir) {
        string fullName(dirName);
        analyzer::analize(analyzer::parse(fullName.append("/").append(file).data()));
    }
    return 0;
}