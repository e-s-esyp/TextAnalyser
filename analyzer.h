#ifndef ANALIZER_PARSER_H
#define ANALIZER_PARSER_H

#include "mainStructure.h"
#include <list>

namespace analyzer {
    using namespace std;

    list<S> *parse(const char *fileName);

    void analize(list<S> *data);
};

#endif //ANALIZER_PARSER_H
