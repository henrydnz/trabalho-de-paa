#include "utils.hpp"

bool isPosInteger(string s){
    if(s.empty()) 
        return false;

    for(char c : s) 
        if(!isdigit(c)) return false;

    return true;
}

static void newFolder(string path){
    try { filesystem::create_directories(path); }
    catch (const filesystem::filesystem_error& e) {
        cerr << "Nao foi possivel criar a pasta " << path << " - Erro: " << e.what() << endl;
    }
}

void createFolders(){
    newFolder(INPUT_PATH);
    newFolder(LOGS_PATH);
    newFolder(DOT_PATH);
    newFolder(IMAGE_VIEW_PATH);
}

bool getGraphView(string filename){
    logsUtil.log("gerando visualizacao de " + filename + ".dot");

    string input = DOT_PATH + filename + ".dot";
    string output = IMAGE_VIEW_PATH + filename + ".png";

    stringstream cmd;
    cmd << GRAPHVIZ_PATH << " -Tpng " << input << " -o " << output;

    logsUtil.log("Executou system(" + cmd.str() + ");");

    int result = system(cmd.str().c_str());

    stringstream msg;

    if (result != 0) {
        msg << "Erro ao gerar a visualizacao (\'" << output << "\')";
        cerr << msg.str() << endl;
        logsUtil.log(msg.str(),1);

        return false;
    }

    msg << "Visualizacao gerada: " << output;
    cout << msg.str() << endl;
    logsUtil.log(msg.str());

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