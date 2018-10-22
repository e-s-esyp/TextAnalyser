#include "logger.h"
#include <iostream>

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

    void put(const char *message) {
        timeStamp();
        cout << message << endl;
    }
}
