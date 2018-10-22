#include "logger.h"
#include <iostream>
#include <cstdarg>

namespace logger {
    using namespace std;

    void timeStamp() {
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        char timeString[128];
        strftime(timeString, 80, "%Y.%m.%d %T ", timeinfo);
        cout << timeString;
    }

    char buffer[1000];

    void put(const char *format, ...) {
        timeStamp();
        va_list args;
        va_start (args, format);
        vsprintf(buffer, format, args);
        cout << buffer << endl;
        va_end (args);
    }
}
