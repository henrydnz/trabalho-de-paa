#include "utils.hpp"

bool isPosInteger(string s){
    if(s.empty()) 
        return false;

    for(char c : s) 
        if(!isdigit(c)) return false;

    return true;
}

bool getGraphView(string dotFilePath, string viewFilePath){
    stringstream cmd;
    cmd << GRAPHVIZ_PATH << " -Tpng " << dotFilePath<< " -o " << viewFilePath;

    int result = system(cmd.str().c_str());

    if (result != 0) {
        string err = "Erro ao gerar a visualizacao do grafo.";
        cerr << err << endl;
        logsUtil.log(err,1);
        return false;
    }

    string msg = "Visualizacao do grafo gerada.";
    cout << msg << endl;
    logsUtil.log(msg);

    return true;
}

void LogsUtil::log(const string& mensagem, int flag) {
    string tipo;

    switch (flag) {
        case 0: tipo = "[INFO] "; break;
        case 1: tipo = "[ERRO] "; break;
        case 2: tipo = "[AVISO] "; break;
        case 3: tipo = ""; break;
        default: tipo = "[DESCONHECIDO] "; break;
    }

    ofstream logs(LOGFILE_PATH, ios::app);

    if(!logs.is_open()){
        cerr << "Erro na criacao do arquivo de logs." << endl;
        return;
    }

    logs << tipo << mensagem << '\n';
}

void LogsUtil::resetLog(){ofstream logs(LOGFILE_PATH, ios::trunc);}

void wrongInputFileFormat(int lineNum, string expected, string got){
    logsUtil.log("Formatacao do arquivo errada na linha "
        +to_string(lineNum)+"!\nEsperado:"+expected
        +".\nLido: "+got, 1);
}