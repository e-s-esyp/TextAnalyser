#include <cstdarg>
#include "stringLogger.h"
#include "logger.h"

stringLogger *stringLogger::put(const char *format, ...) {
    va_list args;
    va_start (args, format);
    vsprintf(buffer, format, args);
    data.append(buffer);
    va_end (args);
    return this;
}

stringLogger *stringLogger::putTimed(const char *format, ...) {
    data.append(logger::getTimeStamp());
    va_list args;
    va_start (args, format);
    vsprintf(buffer, format, args);
    data.append(buffer);
    va_end (args);
    data.append("\n");
    return this;
}

string stringLogger::get() {
    return data;
}
