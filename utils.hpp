#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>

#define LOGFILE_NAME "logs.txt"

using namespace std;

ifstream getFile(string filename);
bool isPosInteger(string s);

void writeLog(string msg);

#endif