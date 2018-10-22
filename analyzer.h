#ifndef ANALIZER_PARSER_H
#define ANALIZER_PARSER_H

#include "mainStructure.h"
#include <list>

#define MAX_BUF_SIZE 200000000
namespace analyzer {
    using namespace std;

    list<S> *parse(const char *fileName);

    void analize(list<S> *data);
};

#endif //ANALIZER_PARSER_H
