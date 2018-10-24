#ifndef ANALIZER_LINEPARSERCHAR_H
#define ANALIZER_LINEPARSERCHAR_H

#include "mainStructure.h"
#include "stringLogger.h"
#include <list>

namespace lineParserChar {
    using namespace std;

    list<S> *parseBufferAndDelete(const char *buffer, long actualBufferSize, stringLogger &logger);
}

#endif //ANALIZER_LINEPARSERCHAR_H
