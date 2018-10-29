#include "lineParserChar.h"
#include "myStrings.cpp"

namespace lineParserChar {
    using namespace std;

    class parser {

        list<S> *dataList;
        char *buffer;
        const char *bufferHead;
        long bufferHeadIndex;
        long actualBufferSize;
        stringLogger *logger;
        int *lineNum;
        long lineStartIndex;
        char *lineData;
        bool isFileEnd;
        long patternPlace;

        inline void newLine() {
            lineStartIndex = bufferHeadIndex;
            (*lineNum)++;
//            getLine();
//            logger->put("%d: %s\n", *lineNum, lineData);
        }

        void skipInt() {
            while (myStrings::isDecimal(*bufferHead) && (bufferHeadIndex < actualBufferSize)) {
                bufferHead++;
                bufferHeadIndex++;
            }
        }

        inline void parseInt(int &n) {
            n = 0;
            while (myStrings::isDecimal(*bufferHead) && (bufferHeadIndex < actualBufferSize)) {
                n = n * 10 + *(bufferHead++) - '0';
                bufferHeadIndex++;
            }
        }

        inline bool parseCheck(const char pattern[3]) {
            patternPlace = bufferHeadIndex - lineStartIndex;
            while (*pattern && (*bufferHead == *pattern) &&
                   (bufferHeadIndex < actualBufferSize)) {
                bufferHead++;
                bufferHeadIndex++;
                pattern++;
            }
            return *pattern;
        }

        void getLine() {
            char *k = lineData;
            const char *l = buffer + lineStartIndex;
            long lineCheckIndex = 0;
            int n = 0;
            while ((*l != '\n') && (lineCheckIndex < actualBufferSize) && (n < 999)) {
                *(k++) = *(l++);
                lineCheckIndex++;
                n++;
            }
            *k = 0;
        }

        void printError(const char pattern[3]) {
            getLine();
            logger->put("Error:  row %d data (%s) corrupt, on place %d must be (%s)\n", *lineNum,
                        lineData, patternPlace, pattern);
            while ((*bufferHead != '\n') && (bufferHeadIndex < actualBufferSize)) {
                bufferHead++;
                bufferHeadIndex++;
            };
            if (bufferHeadIndex < actualBufferSize) {
                bufferHead++;
                bufferHeadIndex++;
            }
        }

        long parseBack() {
            if (isFileEnd) return 0;
            (*lineNum)--;
            myStrings::copy0(buffer, buffer + lineStartIndex, actualBufferSize - lineStartIndex);
//            logger->put("ParseBack %d %d: %s\n", dataList->size(), actualBufferSize - lineStartIndex,
//                        buffer);
            return actualBufferSize - lineStartIndex;
        }

    public:
        parser(list<S> *dataList_, char *buffer_, long actualBufferSize_, bool isFileEnd_,
               stringLogger *logger_, long &lastRemainsSize_, int *numLines) {
            dataList = dataList_;
            buffer = buffer_;
            bufferHead = buffer_;
            bufferHeadIndex = 0;
            actualBufferSize = actualBufferSize_;
            logger = logger_;
            isFileEnd = isFileEnd_;
            lineNum = numLines;
            lineStartIndex = 0;
            lineData = new char[1000];
            patternPlace = 0;
        }

        ~parser() {
            delete[]lineData;
        }

        long parse() {
            S s{};
            while (true) {
                newLine();
                parseInt(s.time);
                if (parseCheck(", ")) {
                    if (bufferHeadIndex >= actualBufferSize) {
                        if (isFileEnd) printError(", ");
                        break;
                    } else {
                        printError(", ");
                        continue;
                    }
                };
                parseInt(s.value);
                if (parseCheck(", ")) {
                    if (bufferHeadIndex >= actualBufferSize) {
                        if (isFileEnd) printError(", ");
                        break;
                    } else {
                        printError(", ");
                        continue;
                    }
                };
                skipInt();
                if (parseCheck(", ")) {
                    if (bufferHeadIndex >= actualBufferSize) {
                        if (isFileEnd) printError(", ");
                        break;
                    } else {
                        printError(", ");
                        continue;
                    }
                };
                skipInt();
                if (bufferHeadIndex >= actualBufferSize) {
                    if (isFileEnd) dataList->push_back(s);
                    break;
                } else {
                    if (parseCheck("\n")) {
                        if (bufferHeadIndex >= actualBufferSize) {
                            if (isFileEnd) printError("\\n");
                            break;
                        } else {
                            printError("\\n");
                            continue;
                        }
                    }
                    dataList->push_back(s);
                }
            }
            return parseBack();
        }
    };

    void parseBuffer(list<S> *dataList, char *buffer, long actualBufferSize, bool isFileEnd,
                     stringLogger *logger, long &lastRemainsSize, int *numLines) {
        parser par(dataList, buffer, actualBufferSize, isFileEnd, logger, lastRemainsSize, numLines);
        lastRemainsSize = par.parse();
    }
}

