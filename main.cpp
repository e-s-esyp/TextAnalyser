#include <iostream>
#include "logger.h"
#include "dirAnalyzer.h"
#include "myStrings.cpp"

using namespace std;

int main(int argc, char **argv) {
    logger::putTimed("Starting. WARNING: max file size %d byte", MAX_BUF_SIZE);
    auto subdirs = dirAnalyzer::getSubDirs(".");
    int i = 0;
    for (const auto &subdir:*subdirs) {
        logger::put("%2d %s\n", i++, subdir.data());
    }
    string choose;
    if (argc != 2 || !myStrings::isEqual(argv[1], "-a")) {
        logger::put("Choose index or 'a' for all: ");
        cin >> choose;
        if (choose == "a") {
            for (const auto &subdir:*subdirs) {
                dirAnalyzer::analyze(subdir.data());
            }
        } else {
            //TODO
        }
    } else {
        for (const auto &subdir:*subdirs) {
            dirAnalyzer::analyze(subdir.data());
        }
    }
    delete subdirs;
    return 0;
}