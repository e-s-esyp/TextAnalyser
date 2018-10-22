#include "myStrings.h"
#include "logger.h"
#include "lineParserStringStream.h"
#include <iostream>
#include <sstream>


namespace lineParserStringStream {
    using namespace std;

#define INIT int n; char a[10];
#define ERROR_CASE(Y) {\
    cout << "Error:" << " row " << lineNum << " place "<< (Y) << " data corrupt (" << lineData << ")" <<"\n";\
    continue;\
}
#define PARSE_INT(X, Y) if (!(line >> (X))) ERROR_CASE(Y)
#define CHECK_INT(Y)  if (!(line >> n)) ERROR_CASE(Y)
#define CHECK_STRING(X, Z, Y) line.read(a, Z);\
    a[Z] = 0;\
    if (!myStrings::isEqual(a, X)) {\
    cout << "\"" << a << "\" != \"" << (X) << "\"" << endl;\
    ERROR_CASE(Y)\
}

    list<S> *parseBufferAndDelete(const char *const buffer) {
        auto dataList = new list<S>;
        stringstream fileString(buffer);
        delete buffer;
        string lineData;
        int lineNum = 0;
        while (getline(fileString, lineData, '\n')) {
            lineNum++;
            stringstream line(lineData);
            S s{};
            INIT
            PARSE_INT(s.time, 1)
            CHECK_STRING(", ", 2, 2)
            PARSE_INT(s.value, 3)
            CHECK_STRING(", ", 2, 4)
            CHECK_INT(5)
            CHECK_STRING(", ", 2, 6)
            CHECK_INT(7)
            dataList->push_back(s);
        }
        logger::timeStamp();
        cout << "Total: " << lineNum << " lines.\n";
        return dataList;
    }

#undef INIT
#undef ERROR_CASE
#undef PARSE_INT
#undef CHECK_INT
#undef CHECK_STRING
}

