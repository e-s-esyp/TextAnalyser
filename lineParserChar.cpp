#include "lineParserChar.h"
#include "logger.h"
#include <iostream>

namespace lineParserChar {
    using namespace std;
#define IS_DECIMAL(X) ('0' <= (X) && (X) <= '9')
#define INT(X)\
    {\
        int n = 0;\
        while (IS_DECIMAL(*bufferHead) && (bufferHeadIndex < actualBufferSize)) {\
            n = n * 10 + *(bufferHead++) - '0';\
            bufferHeadIndex++;\
        }\
        (X) = n;\
    }
#define SKIP_INT\
    while (IS_DECIMAL(*bufferHead) && (bufferHeadIndex < actualBufferSize)) {\
        bufferHead++;\
        bufferHeadIndex++;\
    }
#define CHECK(X)\
    {\
        long patternPlace = bufferHeadIndex - lineStartIndex;\
        const char *patternHead = X;\
        while (*patternHead && (*bufferHead == *patternHead) && (bufferHeadIndex < actualBufferSize)) {\
            bufferHead++;\
            bufferHeadIndex++;\
            patternHead++;\
        }\
        if (*patternHead && (bufferHeadIndex < actualBufferSize || (X) != lineDelimiter)) {\
            char *k = lineData;\
            const char *l = buffer + lineStartIndex;\
            long lineCheckIndex = 0;\
            while ((*l != '\n') && (lineCheckIndex < actualBufferSize)) {\
                *(k++) = *(l++);\
                lineCheckIndex++;\
            }\
            *k = 0;\
            cout << "Error:" << " row " << lineNum << " data (" << lineData << ") corrupt," << " on place "<< patternPlace << " must be ("<< (X) <<")\n";\
            while ((*bufferHead != '\n') && (bufferHeadIndex < actualBufferSize)) {\
                bufferHead++;\
                bufferHeadIndex++;\
            };\
            if (bufferHeadIndex < actualBufferSize){\
                bufferHead++;\
                bufferHeadIndex++;\
            }\
            continue;\
        }\
    }\

    list<S> *parseBufferAndDelete(const char *const buffer, const long actualBufferSize) {
        auto dataList = new list<S>;
        const char *bufferHead = buffer;
        long bufferHeadIndex = 0;
        S s{};
        const char *delimiter = ", ";
        const char *lineDelimiter = "\n";
        int lineNum = 0;
        char lineData[1000];
        long lineStartIndex;
        while (bufferHeadIndex < actualBufferSize) {
            lineStartIndex = bufferHeadIndex;
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

