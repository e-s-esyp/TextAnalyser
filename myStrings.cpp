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
}
