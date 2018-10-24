#include "analyzer.h"
#include "lineParserChar.h"
#include <fstream>

void fileAnalyzer::parse() {
    report.putTimed("File: %s", name.data());
    ifstream file(name, ios::binary);
    auto buffer = new char[MAX_BUF_SIZE];
    file.read(buffer, MAX_BUF_SIZE - 1);
    const long actualBufferSize = file.gcount();
    file.close();
    report.putTimed("File read.");
    data = lineParserChar::parseBufferAndDelete(buffer, actualBufferSize, report);
}

void fileAnalyzer::analyze() {
    data->sort([&](S a, S b) { return a.value < b.value; });
    report.putTimed("Sort done");
    auto finish = data->end();
    for (int i = 0; i < 20 && finish != data->begin(); ++i) finish--;
    auto it = data->begin();
    long sum = 0;
    int num = 0;
    report.put("%8s %8s %8s %8s\n", "num", "value", "when", "average");
    report.put("%8s %8s %8s %8s\n", "", "", "", "value");
    if (it != finish) {
        for (; it != finish; ++it) {
            sum += it->value;
            ++num;
            if (num < 5) {
                report.put("%8d %8d %8d %8ld\n", num, it->value, it->time, sum / num);
            }
        }
        report.put("....\n");
    }
    for (; it != data->end(); ++it) {
        sum += it->value;
        ++num;
        report.put("%8d %8d %8d %8ld\n", num, it->value, it->time, sum / num);
    }
    delete (data);
}

void fileAnalyzer::perform() {
    parse();
    analyze();
}

string fileAnalyzer::getReport() {
    if (executor.joinable()) {
        executor.join();
        report.putTimed("Finish ------------------------------");
    }
    return report.get();
}

void theFunction(fileAnalyzer *a) {
    a->perform();
}

void fileAnalyzer::performInThread() {
    report.put("\n")->putTimed("Start -------------------------------");
    executor = thread(theFunction, this);
}

