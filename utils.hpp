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

class Logs_Util {
private:
    Logs_Util() = default;

public:
    Logs_Util(const Logs_Util&) = delete;
    Logs_Util& operator=(const Logs_Util&) = delete;

    static Logs_Util& getInstance() {
        static Logs_Util instance;
        return instance;
    }

    void log(const std::string& mensagem) {
        log(mensagem, 0);
    }

    void log(const std::string& mensagem, int flag) {
        std::string tipo;

        switch (flag) {
            case 0: tipo = "INFO"; break;
            case 1: tipo = "ERRO"; break;
            case 2: tipo = "AVISO"; break;
            default: tipo = "DESCONHECIDO"; break;
        }

        std::ofstream arquivo("logs.txt", std::ios::app);

        if (arquivo.is_open()) {
            arquivo << "[" << tipo << "] " << mensagem << '\n';
        }
    }
};

inline Logs_Util& logs_util = Logs_Util::getInstance();

#endif