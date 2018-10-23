#include "logger.h"
#include "dirAnalyzer.h"
#include "analyzer.h"

using namespace std;

int main(int argc, char **argv) {
    logger::put("Starting. WARNING: max file size %d byte", MAX_BUF_SIZE);
    auto dir = dirAnalyzer::getList((argc == 2) ? argv[1] : ".");
    dir->sort();
    logger::put("Have a dirList");
    for (const auto &file:*dir) {
        analyzer::analize(analyzer::parse(file.data()));
    }
    return 0;
}