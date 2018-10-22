#include "lineParserChar.h"
namespace lineParserChar {
    list<S> *parseBufferAndDelete(const char *const buffer) {
        auto dataList = new list<S>;
        auto i = buffer;

        delete buffer;
        return dataList;
    }
}

