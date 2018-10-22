#include "analyzer.h"
#include "logger.h"
#include "lineParserStringStream.h"
#include <iostream>
#include <fstream>

namespace analyzer {
    using namespace std;

    list<S> *parse(const char *const fileName) {
        logger::timeStamp();
        cout << "File: " << fileName << endl;
        ifstream file(fileName, ios::binary);
        auto buffer = new char[MAX_BUF_SIZE];
        file.read(buffer, MAX_BUF_SIZE);
        file.close();
        logger::put("File read.");
        return lineParserStringStream::parseBufferAndDelete(buffer);
    }

    void analize(list<S> *data) {
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

};

