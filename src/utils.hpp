#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <limits>

#include "graph.hpp"

#define REGEX_INPUT_FILE_FIRST_LINE R"(^orientado=(sim|nao)$)"
#define REGEX_INPUT_FILE_SECOND_LINE R"(^V=([0-9]+)$)"
#define REGEX_INPUT_FILE_EDGES R"(^\(([0-9]+),([0-9]+)\):(-?[0-9]+)$)"
#define LOGFILE_PATH "..\\logs\\logs.txt"

#define GRAPHVIZ_PATH "\"C:\\Program Files (x86)\\Graphviz\\bin\\dot.exe\""
#define DOTFILE_PATH "..\\graph-view\\graphView.dot"
#define VIEWPNGFILE_PATH "..\\graph-view\\graphView.png"

#define INT_INF numeric_limits<int>::max()

using namespace std;

bool isPosInteger(string s);
bool getGraphView(string dotFilePath, string viewFilePath);

class LogsUtil {
private:
    LogsUtil() = default;

public:
    LogsUtil(const LogsUtil&) = delete;
    LogsUtil& operator=(const LogsUtil&) = delete;

    static LogsUtil& getInstance() {
        static LogsUtil instance;
        return instance;
    }

    void log(const string& mensagem, int flag = 0);
    void resetLog();
};

inline LogsUtil& logsUtil = LogsUtil::getInstance();

void wrongInputFileFormat(int lineNum, string expected, string got);

#endif