#include "logger.h"
#include "dirAnalyzer.h"
#include "analyzer.h"

using namespace std;

int main(int argc, char **argv) {
    logger::putTimed("Starting. WARNING: max file size %d byte", MAX_BUF_SIZE);
    auto dirName = (argc == 2) ? argv[1] : ".";
    dirAnalyzer::analyze(dirName);

    return 0;
}