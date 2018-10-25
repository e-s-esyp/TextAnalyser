#ifndef ANALIZER_STRINGLOGGER_H
#define ANALIZER_STRINGLOGGER_H

#include <string>

using namespace std;

class stringLogger {
    string data;
    char buffer[10000];

public:
    stringLogger *put(const char *format, ...);

    stringLogger *putTimed(const char *format, ...);

    string get();
};

#endif //ANALIZER_STRINGLOGGER_H
