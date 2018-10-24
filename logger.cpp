#include "logger.h"
#include <iostream>
#include <cstdarg>

namespace logger {

    string getTimeStamp() {
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        char timeString[128];
        strftime(timeString, 80, "%Y.%m.%d %T ", timeinfo);
        return string(timeString);
    }

    void timeStamp() {
        cout << getTimeStamp();
    }

    void put(const char *format, ...) {
        timeStamp();
        va_list args;
        va_start (args, format);
        char buffer[1000];
        vsprintf(buffer, format, args);
        cout << buffer << endl;
        va_end (args);
    }
}
