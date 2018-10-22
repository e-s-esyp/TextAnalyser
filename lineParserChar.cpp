#include "lineParserChar.h"
#include "logger.h"
#include <iostream>

namespace lineParserChar {
    using namespace std;
#define IS_DECIMAL(X) ('0' <= (X) && (X) <= '9')
#define INT(X) n = 0;\
    while (IS_DECIMAL(*i)) {\
        n = n * 10 + *(i++) - '0';\
    }\
    (X) = n;
#define SKIP_INT while (IS_DECIMAL(*i)) {\
        i++;\
    }
#define CHECK(X) j = X;\
    place = 0;\
    while (*i && *j && (*i == *j) && (place < 1000) && (bufferPlaceCheck < MAX_BUF_SIZE)) {\
        i++;\
        j++;\
        place++;\
        bufferPlaceCheck++;\
    }\
    if (*i && *j) {\
        char *k = lineData;\
        const char *l = lineStart;\
        int placeCheck = 0;\
        while ((*l != '\n') && *l && (placeCheck < 1000)) {\
            *(k++) = *(l++);\
            placeCheck++;\
        }\
        *k = 0;\
        cout << "Error:" << " row " << lineNum << " place "<< place << " data corrupt (" << lineData << ") must be ("<< (X) <<")\n";\
        placeCheck = 0;\
        while ((*i != '\n') && *i && (bufferPlaceCheck < MAX_BUF_SIZE)) {\
            i++;\
            bufferPlaceCheck++;\
        };\
        if (*i == '\n'){\
            i++;\
            bufferPlaceCheck++;\
        }\
        continue;\
    }

    list<S> *parseBufferAndDelete(const char *const buffer) {
        auto dataList = new list<S>;
        const char *i = buffer;
        S s{};
        int n;
        const char *j;
        const char *delimiter = ", ";
        const char *lineDelimiter = "\n";
        int lineNum = 0;
        char lineData[1000];
        int place = 0;\
        const char *lineStart;
        int bufferPlaceCheck = 0;
        while (*i) {
            lineStart = i;
            lineNum++;
            INT(s.time)
            CHECK(delimiter)
            INT(s.value)
            CHECK(delimiter)
            SKIP_INT
            CHECK(delimiter)
            SKIP_INT
            CHECK(lineDelimiter)
            dataList->push_back(s);
        }
        logger::timeStamp();
        cout << "Total: " << lineNum << " lines.\n";
        delete buffer;
        return dataList;
    }
}

