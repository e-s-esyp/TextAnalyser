#include <iostream>
#include <map>
#include "logger.h"
#include "dirAnalyzer.h"
#include "myStrings.cpp"

using namespace std;

void printDefault() {
    logger::put("Analyzer options:\n");
    logger::put("-j=<num threads>\n");
    logger::put("-maindir=<dir name, where subdirs will be analyzed>\n");
    logger::put("-dir=<dir name, where .log files will be analyzed>\n");
}

class arguments {
public:
    map<string, string> assigns;
    bool error = false;

    arguments(int argc, char **argv) {
        for (int i = 1; i < argc; i++) {
            string s(argv[i]);
            if (s.length() < 3 || s[0] != '-') {
                error = true;
                return;
            }
            unsigned long p = s.find('=');
            if (p != string::npos) {
                assigns[s.substr(1, p - 1)] = s.substr(p + 1, string::npos);
            } else {
                error = true;
                return;
            }
        }
    }
};

int main(int argc, char **argv) {
    logger::putTimed("Starting. WARNING: max file size %d byte", MAX_BUF_SIZE);
    arguments args(argc, argv);
    if (args.error) {
        printDefault();
        return -1;
    }
    int numThreads = 1;
    if (args.assigns.find("j") != args.assigns.end()) {
        numThreads = stoi(args.assigns["j"]);
        args.assigns.erase("j");
    }
    logger::put("Number of used threads at one time = %d\n", numThreads);
    string mainDir(".");
    if (args.assigns.find("maindir") != args.assigns.end()) {
        mainDir = args.assigns["maindir"];
        args.assigns.erase("maindir");
    }
    bool allDirs = true;
    if (args.assigns.find("dir") != args.assigns.end()) {
        allDirs = false;
        args.assigns.erase("dir");
    }
    if (!args.assigns.empty()) {
        printDefault();
        return -1;
    }
    if (allDirs) {
        logger::put("Processing all subdirs:\n");
        auto subDirs = dirAnalyzer::getSubDirs(mainDir.data());
        int i = 0;
        for (const auto &subdir:*subDirs) {
            logger::put("%2d %s\n", i++, subdir.data());
        }
        for (const auto &subdir:*subDirs) {
            dirAnalyzer::analyze(subdir.data(), numThreads);
        }
        delete subDirs;
    } else {
        dirAnalyzer::analyze(args.assigns["dir"].data(), numThreads);
    }
    return 0;
}