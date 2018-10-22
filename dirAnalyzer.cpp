#include "dirAnalyzer.h"
#include "myStrings.h"
#include <dirent.h>

namespace dirAnalyzer {
    list <string> *getList(const char *dirName, const char *filter) {
        auto result = new list<string>;
        auto dirp = opendir(dirName);
        dirent *dp;
        while ((dp = readdir(dirp)) != nullptr) {
            if (myStrings::endsWith(dp->d_name, filter))
                result->push_back(dp->d_name);
        }
        closedir(dirp);
        return result;
    }
};

