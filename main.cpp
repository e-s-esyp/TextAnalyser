#include <iostream>
#include <list>
#include <sstream>
#include <fstream>
#include <dirent.h>

using namespace std;
struct S {
    int time;
    int value;
};

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

namespace parser {
    int lineNum = 0;
    string lineData;

#define INIT int n; char a[10];
#define ERROR_CASE(Y) {\
    cout << "Error:" << " row " << lineNum << " place "<< (Y) << " data corrupt (" << lineData << ")" <<"\n";\
    return;\
}
#define PARSE_INT(X, Y) if (!(line >> (X))) ERROR_CASE(Y)
#define CHECK_INT(Y)  if (!(line >> n)) ERROR_CASE(Y)
#define CHECK_STRING(X, Z, Y) line.read(a, Z);\
    a[Z] = 0;\
    if (!myStrings::isEqual(a, X)) {\
    cout << "\"" << a << "\" != \"" << (X) << "\"" << endl;\
    ERROR_CASE(Y)\
}

    void parseLine(list<S> *data) {
        stringstream line(lineData);
        S s{};
        INIT
        PARSE_INT(s.time, 1)
        CHECK_STRING(", ", 2, 2)
        PARSE_INT(s.value, 3)
        CHECK_STRING(", ", 2, 4)
        CHECK_INT(5)
        CHECK_STRING(", ", 2, 6)
        CHECK_INT(7)
        data->push_back(s);
    }

#undef INIT
#undef ERROR_CASE
#undef PARSE_INT
#undef CHECK_INT
#undef CHECK_STRING

    list<S> *parse(const char *fileName) {
        cout << "File: " << fileName << endl;
        auto data = new list<S>;
        ifstream file(fileName);
        while (getline(file, lineData, '\n')) {
            lineNum++;
            parseLine(data);
        }
        file.close();
        cout << "Total: " << lineNum << " lines.\n";
        return data;
    }
};

namespace dirAnalyzer {
    list<string> *getList(const char *dirName, const char *filter = ".log") {
        auto result = new list<string>;
        auto dirp = opendir(dirName);
        dirent *dp;
        while ((dp = readdir(dirp)) != nullptr) {
            if (myStrings::endsWith(dp->d_name, filter))
                result->push_back(dp->d_name);
        }
        closedir(dirp);
        return result;
    }
};

void analize(const char *name) {
    auto data = parser::parse(name);
    data->sort([&](S a, S b) { return a.value < b.value; });
    auto it = data->end();
    for (int i = 0; i < 10 && it != data->begin(); ++i) it--;
    for (; it != data->end(); ++it) {
        cout << it->time << ": " << it->value << endl;
    }
    delete (data);
}

int main(int argc, char **argv) {
    auto dir = dirAnalyzer::getList((argc == 2) ? argv[1] : ".");
    for (const auto &file:*dir) {
        analize(file.data());
    }
    return 0;
}