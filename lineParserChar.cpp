#include "lineParserChar.h"
#include "myStrings.cpp"

namespace lineParserChar {
    using namespace std;

    class parser {

    public:
        const char *buffer;
        const char *bufferHead;
        long bufferHeadIndex;
        long actualBufferSize;
        stringLogger *logger;
        int lineNum;
        long lineStartIndex;
        char *lineData;

        parser(const char *buffer_, const long actualBufferSize_, stringLogger *logger_) {
            buffer = buffer_;
            bufferHead = buffer_;
            bufferHeadIndex = 0;
            actualBufferSize = actualBufferSize_;
            logger = logger_;
            lineNum = 0;
            lineStartIndex = 0;
            lineData = new char[1000];
        }

        ~parser() {
            delete[]lineData;
        }

        inline bool canContinue() {
            return bufferHeadIndex < actualBufferSize;
        }

        inline void newLine() {
            lineStartIndex = bufferHeadIndex;
            lineNum++;
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

        inline bool parseCheck(const char *pattern) {
            long patternPlace = bufferHeadIndex - lineStartIndex;
            const char *patternHead = pattern;
            while (*patternHead && (*bufferHead == *patternHead) &&
                   (bufferHeadIndex < actualBufferSize)) {
                bufferHead++;
                bufferHeadIndex++;
                patternHead++;
            }
            if (*patternHead && (bufferHeadIndex < actualBufferSize ||
                                 !myStrings::isEqual(pattern, "\n"))) {
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
                logger->put("Error:  row %d data (%s) corrupt, on place %d must be (%s)\n", lineNum,
                            lineData, patternPlace, pattern);
                while ((*bufferHead != '\n') && (bufferHeadIndex < actualBufferSize)) {
                    bufferHead++;
                    bufferHeadIndex++;
                };
                if (bufferHeadIndex < actualBufferSize) {
                    bufferHead++;
                    bufferHeadIndex++;
                }
                return true;
            }
            return false;
        }
    };

    list<S> *parseBuffer(const char *buffer, const long actualBufferSize, stringLogger &logger) {
        auto dataList = new list<S>;
        parser par(buffer, actualBufferSize, &logger);
        S s{};
        while (par.canContinue()) {
            par.newLine();
            par.parseInt(s.time);
            par.parseCheck(", ");
            par.parseInt(s.value);
            if (par.parseCheck(", ")) continue;
            par.skipInt();
            if (par.parseCheck(", ")) continue;
            par.skipInt();
            if (par.parseCheck("\n")) continue;
            dataList->push_back(s);
        }
        logger.putTimed("Total: %d lines.", par.lineNum);
        return dataList;
    }
}

