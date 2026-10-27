#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <limits>
#include <filesystem>

#include "graph.hpp"

#define REGEX_INPUT_FILE_FIRST_LINE R"(^orientado=(sim|nao)$)"
#define REGEX_INPUT_FILE_SECOND_LINE R"(^V=([0-9]+)$)"
#define REGEX_INPUT_FILE_EDGES R"(^\(([0-9]+),([0-9]+)\):(-?[0-9]+)$)"


#define GRAPHVIZ_PATH "\"C:\\Program Files (x86)\\Graphviz\\bin\\dot.exe\""

#define LOGFILE_PATH "..\\logs\\logs.txt"

#define INPUT_PATH "..\\input\\"
#define LOGS_PATH "..\\logs\\"
#define DOT_PATH "..\\graph-view\\dot-files\\"
#define IMAGE_VIEW_PATH "..\\graph-view\\image-files\\"

#define INT_INF numeric_limits<int>::max()

using namespace std;

bool isPosInteger(string s);
bool getGraphView(string filename);
void createFolders();

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