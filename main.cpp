#include "lineParserStringStream.h"
#include "logger.h"
#include "dirAnalyzer.h"
#include <iostream>
#include <fstream>

using namespace std;

namespace parser {
    list<S> *parse(const char *fileName) {
        logger::timeStamp();
        cout << "File: " << fileName << endl;
        ifstream file(fileName, ios::binary);
        int bufferLength = 200000000;
        auto buffer = new char[bufferLength];
        file.read(buffer, bufferLength);
        file.close();
        logger::put("File read.");
        return lineParserStringStream::parseBufferAndDelete(buffer);
    }
};

void analize(const char *name) {
    auto data = parser::parse(name);
    data->sort([&](S a, S b) { return a.value < b.value; });
    logger::put("Sort done");
    auto finish = data->end();
    for (int i = 0; i < 20 && finish != data->begin(); ++i) finish--;
    auto it = data->begin();
    long sum = 0;
    int num = 0;
    printf("%8s %8s %8s %8s\n", "num", "value", "when", "average");
    printf("%8s %8s %8s %8s\n", "", "", "", "value");
    if (it != finish) {
        for (; it != finish; ++it) {
            sum += it->value;
            ++num;
            if (num < 5) {
                printf("%8d %8d %8d %8ld\n", num, it->value, it->time, sum / num);
            }
        }
        cout << "....\n";
    }
    for (; it != data->end(); ++it) {
        sum += it->value;
        ++num;
        printf("%8d %8d %8d %8ld\n", num, it->value, it->time, sum / num);
    }
    delete (data);
}

int main(int argc, char **argv) {
    logger::put("Starting. WARNING: max file size 200 000 000 byte");
    auto dir = dirAnalyzer::getList((argc == 2) ? argv[1] : ".");
    logger::put("Have a dirList");
    for (const auto &file:*dir) {
        analize(file.data());
    }
    return 0;
}