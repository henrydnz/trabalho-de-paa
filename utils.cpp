#include "utils.hpp"

ifstream getFile(string filename){
    ifstream file(filename);

    if(!file.is_open()) {
        cerr << "Erro ao abrir " << filename << endl;
        return nullptr;
    }

    return file;
}

bool isPosInteger(string s){
    if(s.empty()) return false;
    for(char c : s) 
        if(!isdigit(c)) return false;
    return true;
}

void writeLog(string msg){
    ifstream logfile = getFile(LOGFILE_NAME);


}