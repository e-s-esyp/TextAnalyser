#include "analyzer.h"
#include "lineParserChar.h"
#include <fstream>

void fileAnalyzer::parse() {
    //TODO: make buffer less then filesize
    report.putTimed("File: %s", name.data());
    ifstream file(name, ios::binary);
    file.seekg(0, ios_base::end);
    long size = file.tellg();
    if (size > MAX_BUF_SIZE - 1) {
        size = MAX_BUF_SIZE - 1;
    }
    auto buffer = new char[size];
    file.seekg(0, ios_base::beg);
    file.read(buffer, size);
    fileSize = file.gcount();
    for (long i = fileSize; i <= size; ++i) {
        buffer[i] = 0;
    }
    file.close();
    report.putTimed("File read.");
    data = lineParserChar::parseBuffer(buffer, fileSize, report);
    delete[] buffer;
}

void fileAnalyzer::analyze() {
    auto last = data->end();
    report.put("Last time = %d\n", (--last)->time);
    data->sort([&](S a, S b) { return a.value < b.value; });
    report.putTimed("Sort done");
    auto finish = data->end();
    for (int i = 0; i < 20 && finish != data->begin(); ++i) finish--;
    auto it = data->begin();
    long sum = 0;
    int num = 0;
    report.put("%8s %11s %8s %11s\n", "num", "value", "when", "average");
    report.put("%8s %11s %8s %11s\n", "", "", "", "value");
    if (it != finish) {
        for (; it != finish; ++it) {
            sum += it->value;
            ++num;
            if (num < 5) {
                report.put("%8d %11ld %8d %11ld\n", num, it->value, it->time, sum / num);
            }
        }
        report.put("....\n");
    }
    for (; it != data->end(); ++it) {
        sum += it->value;
        ++num;
        report.put("%8d %11ld %8d %11ld\n", num, it->value, it->time, sum / num);
    }
    const int divisions = 100;
    int percentile[divisions + 1];
    int percentIndex = 0;
    long sum2 = 0;
    num = 0;
    int lastnum = 0;
    report.put("%8s %11s %8s %11s %8s %11s\n", "percent", "sum", "num in", "value", "when", "average");
    report.put("%8s %11s %8s %11s %8s %11s\n", "", "", "interval", "", "", "value");
    for (auto elem:*data) {
        sum2 += elem.value;
        ++num;
        if (sum2 >= sum * percentIndex / divisions) {
            percentile[percentIndex] = num - lastnum;
            lastnum = num;
            report.put("%6.1f%2s %11ld %8d %11ld %8d %11ld\n",
                       (sum2 == sum) ? 100 : sum2 * 100.0 / sum, "%",
                       sum2, percentile[percentIndex], elem.value, elem.time, sum2 / num);
            percentIndex++;
        }
    }
    int numOfMaxes = percentile[percentIndex - 1];
    report.put("Num of maxe's = %d (%5.4f%2s)\n", numOfMaxes, num > 0 ? numOfMaxes * 100.0 / num : 0,
               "%");
    delete data;
}

void fileAnalyzer::perform() {
    parse();
    analyze();
    finished = true;
}

string fileAnalyzer::getReport() {
    return report.get();
}

string fileAnalyzer::getName() {
    return name;
}

bool fileAnalyzer::isFinished() {
    return finished;
}

long fileAnalyzer::getFileSize() {
    return fileSize;
}

