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

#define GRAPHVIZ_PATH "C:\\msys64\\ucrt64\\bin\\dot.exe"

#define DOTFILE_PATH "..\\graph-view\\graphView"
#define DOTFILE_PATH_KOSARAJU "..\\graph-view\\graphView_kosaraju"
#define DOTFILE_PATH_KRUSKAL "..\\graph-view\\graphView_kruskal"

#define VIEWPNGFILE_PATH "..\\graph-view\\graphView"
#define VIEWPNGFILE_PATH_KOSARAJU "..\\graph-view\\graphView_kosaraju"
#define VIEWPNGFILE_PATH_KRUSKAL "..\\graph-view\\graphView_kruskal"

#define INT_INF numeric_limits<int>::max()

using namespace std;

/// @brief Verifica se a string eh composta apenas de numeros
/// @param s string a ser verificada
/// @return true se a string possui apenas digitos e false do contrario
bool isPosInteger(string s);

/// @brief Automaticamente executa o dot do Graphviz
/// @param dotFilePath Caminho para o arquivo .dot
/// @param viewFilePath Destino para o PNG gerado
/// @return true se executar com sucesso e false do contrario
bool getGraphView(string dotFilePath, string viewFilePath);

/// @brief Classe auxiliar Singleton para log
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

    /// @brief Funcao para imprimir no arquivo de log
    /// @param mensagem mensagem que sera imprimida
    /// @param flag flag para o tipo de log (0 = Info, 1 = Erro, 2 = Warning, 3 = vazio, default = Desconhecido)
    void log(const string& mensagem, int flag = 0);

    /// @brief Limpa o arquivo de log
    void resetLog();
};

inline LogsUtil& logsUtil = LogsUtil::getInstance();

/// @brief Imprime no log um erro na leitura de uma linha
/// @param lineNum Linha onde o erro foi encontrado
/// @param expected O que era experado
/// @param got O que foi recebido
void wrongInputFileFormat(int lineNum, string expected, string got);

#endif