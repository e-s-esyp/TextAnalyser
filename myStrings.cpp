#ifndef MY_STRINGS_CPP
#define MY_STRINGS_CPP

namespace myStrings {
    inline bool isDecimal(char x) {
        return '0' <= x && x <= '9';
    }

    inline bool isEqual(const char *a, const char *b) {
        while (*a && *b && *a == *b) {
            a++;
            b++;
        }
        return *a == *b;
    }

    inline bool endsWith(char const *name, char const *filter) {
        while (*name) ++name;
        const char *i = filter;
        while (*i) {
            ++i;
            --name;
        }
        return isEqual(name, filter);
    }

    inline void copy0(char *destination, const char *source, long i) {
        for (int j = 0; j < i; ++j) {
            *(destination++) = *(source++);
        }
        *(destination) = 0;
    }
}

#endif //MY_STRINGS_CPP
