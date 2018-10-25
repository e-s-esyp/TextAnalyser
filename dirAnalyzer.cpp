#include "dirAnalyzer.h"
#include "myStrings.cpp"
#include "logger.h"
#include "analyzer.h"
#include <dirent.h>
#include <fstream>

namespace dirAnalyzer {
    list<string> *getList(const char *dirName, const char *filter) {
        auto result = new list<string>;
        auto dirp = opendir(dirName);
        if (dirp != nullptr) {
            dirent *dp;
            string dirNameString(dirName);
            while ((dp = readdir(dirp)) != nullptr) {
                if (myStrings::endsWith(dp->d_name, filter))
                    result->push_back(dirNameString + "/" + string(dp->d_name));
            }
            closedir(dirp);
        }
        return result;
    }

    vector<string> *getSubDirs(const char *dirName) {
        auto result = new vector<string>;
        auto dirp = opendir(dirName);
        if (dirp != nullptr) {
            dirent *dp;
            string dirNameString(dirName);
            while ((dp = readdir(dirp)) != nullptr) {
                if (dp->d_type == DT_DIR && !myStrings::isEqual(dp->d_name, ".") &&
                    !myStrings::isEqual(dp->d_name, ".."))
                    result->push_back(dirNameString + "/" + string(dp->d_name));
            }
            closedir(dirp);
        }
        return result;
    }

    void theFunction(fileAnalyzer *analyzer);

    class threadControl {
    public:
        int id;
        fileAnalyzer *theTask;
        thread theThread;

        explicit threadControl(int id_) {
            id = id_;
            theTask = nullptr;
            theThread;
        }

        void make(fileAnalyzer *analyzer) {
            logger::putTimed("Making task %s on control %d", analyzer->getName().data(), id);
            theTask = analyzer;
            theThread = thread(theFunction, theTask);
        }

        bool tryMake(fileAnalyzer *t) {
            if (theTask != nullptr) {
                if (!theTask->isFinished()) {
                    return false;
                }
                if (theThread.joinable()) {
                    theThread.join();
                }
            }
            make(t);
            return true;
        }
    };

    void theFunction(fileAnalyzer *analyzer) {
        analyzer->perform();
    }

    void analyze(const char *dirName) {
        auto files = dirAnalyzer::getList(dirName);
        files->sort();
        logger::putTimed("Have a dirList:");
        list<fileAnalyzer *> tasks;
        for (const auto &file:*files) {
            logger::put("%s\n", file.data());
            tasks.push_back(new fileAnalyzer(file));
        }
        delete files;
        //TODO: define by argv
        int numControls = 3;
        threadControl *controls[numControls];
        for (int i = 0; i < numControls; i++) {
            controls[i] = new threadControl(i + 1);
        }
        for (const auto task:tasks) {
            for (int i = 0;;) {
                if (controls[i]->tryMake(task)) {
                    break;
                }
                i = (i + 1) % numControls;
            }
        }
        for (const auto &control : controls) {
            if (control->theTask != nullptr) {
                while (!control->theTask->isFinished()) {}
                if (control->theThread.joinable()) {
                    control->theThread.join();
                }
            }
            delete control;
        }
        ofstream output(string(dirName) + ".report");
        for (const auto task:tasks) {
            output << task->getReport();
            delete task;
        }
        output.close();
    }
}

