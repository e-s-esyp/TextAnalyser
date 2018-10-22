#ifndef ANALIZER_LINEPARSERCHAR_H
#define ANALIZER_LINEPARSERCHAR_H

#include "mainStructure.h"
#include <list>

namespace lineParserChar {
    using namespace std;

    list<S> *parseBufferAndDelete(const char * buffer);
}

#endif //ANALIZER_LINEPARSERCHAR_H
