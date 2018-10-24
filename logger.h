#ifndef ANALIZER_LOGGER_H
#define ANALIZER_LOGGER_H

#include <string>

using namespace std;

namespace logger {
    string getTimeStamp();

    void timeStamp();

    void put(const char *format, ...);
}

#endif //ANALIZER_LOGGER_H
