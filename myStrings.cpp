#include "myStrings.h"
namespace myStrings {
    bool isEqual(char *a, const char *b) {
        while (*a && *b && *a == *b) {
            a++;
            b++;
        }
        return *a == *b;
    }

    bool endsWith(char *name, const char *filter) {
        while (*name) ++name;
        const char *i = filter;
        while (*i) {
            ++i;
            --name;
        }
        return isEqual(name, filter);
    }
}
