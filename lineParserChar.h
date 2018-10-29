#ifndef ANALIZER_LINEPARSERCHAR_H
#define ANALIZER_LINEPARSERCHAR_H

#include "mainStructure.h"
#include "stringLogger.h"
#include <list>

namespace lineParserChar {
    using namespace std;

    void
    parseBuffer(list<S> *dataList, char *buffer, long actualBufferSize, bool isFileEnd,
                stringLogger *logger, long &lastRemainsSize, int *numLines);
}

#endif //ANALIZER_LINEPARSERCHAR_H
