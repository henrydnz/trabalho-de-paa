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

// macros de regex string para leitura do grafo.
#define REGEX_INPUT_FILE_FIRST_LINE R"(^orientado=(sim|nao)$)"
#define REGEX_INPUT_FILE_SECOND_LINE R"(^V=([0-9]+)$)"
#define REGEX_INPUT_FILE_EDGES R"(^\(([0-9]+),([0-9]+)\):(-?[0-9]+)$)"

// caminho para o executavel dot do graphviz (mudar se necessario)
#define GRAPHVIZ_PATH "\"C:\\Program Files (x86)\\Graphviz\\bin\\dot.exe\""

// caminho para arquivo de logs
#define LOGFILE_PATH "..\\logs\\logs.txt"

// caminhos para as pastas necessarias para o programa funcionar
#define INPUT_PATH "..\\input\\"
#define LOGS_PATH "..\\logs\\"
#define DOT_PATH "..\\graph-view\\dot-files\\"
#define IMAGE_VIEW_PATH "..\\graph-view\\image-files\\"

// valor int infinito (usado em Dijkstra), valor maximo de int.
#define INT_INF numeric_limits<int>::max()

using namespace std;

/// @brief Verifica se a string eh composta apenas de numeros
/// @param s string a ser verificada
/// @return true se a string possui apenas digitos e false do contrario
bool isPosInteger(string s);

/// @brief Chama o dot.exe do GraphViz pelo GRAPHVIZ_PATH e executa um 
///         comando que cria um .png com base no arquivo filename.dot
/// @param filename O nome do arquivo (sem .dot)
/// @return retorna um valor booleano que diz se a operacao foi concluida com sucesso
bool getGraphView(string filename);

/// @brief  cria as pastas base que o program aprecisa pra funcionar
void createFolders();

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

/// @brief variavel da singleton
inline LogsUtil& logsUtil = LogsUtil::getInstance();

/// @brief Imprime no log um erro na leitura de uma linha
/// @param lineNum Linha onde o erro foi encontrado
/// @param expected O que era experado
/// @param got O que foi recebido
void wrongInputFileFormat(int lineNum, string expected, string got);

#endif