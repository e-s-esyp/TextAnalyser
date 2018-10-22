
#ifndef ANALIZER_LINEPARSERSTRINGSTREAM_H
#define ANALIZER_LINEPARSERSTRINGSTREAM_H

#include "mainStructure.h"
#include <list>

namespace lineParserStringStream {
    using namespace std;

    list <S> *parseBufferAndDelete(const char *const buffer);
}
#endif //ANALIZER_LINEPARSERSTRINGSTREAM_H
