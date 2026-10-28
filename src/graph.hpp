#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <queue>
#include <sstream>

#include "utils.hpp"

using namespace std;

struct Edge {
    int dest, weight;
    Edge(int d, int w):dest(d),weight(w){};
};

// modelo de dados para ligacoes do grafo. cada no possui um vector<Edge> descrevendo suas ligacoes.
typedef vector<vector<Edge>> EdgeTable;
// modelo de dados para representar componentes de Kosaraju. cada componente tem um vector<int> representando os nos que o constituem.
typedef vector<vector<int>> Components;
// modelo de dados para representar as ligacoes da arvore AGM. cada no tem um vector<int> representando nos que se ligam a ele.
typedef vector<vector<int>> TreeEdges;

class Graph {
    private:

    EdgeTable edges;
    int nodeCount;
    bool isOriented;

    /// @brief Funcao responsavel por distribuir uma busca em componentes no grafo, iniciando as recursoes
    /// @param origin Numero do no onde a busca sera iniciada
    /// @param method Ponteiro para a funcao que sera realizada
    /// @param reverseAns Flags para se a resposta precisa ser invertida (como na Topologica)
    /// @return Um vetor de inteiros com a resposta da funcao realizada
    vector<int> search(int origin, void (Graph::*method)(int,vector<bool>&,vector<int>&), bool reverseAns);

    /// @brief Funcao que realiza uma BFS (Breadth First Search) (Recursiva) em um componente.
    /// @param node Numero do no na qual a a busca sera iniciada
    /// @param visited Vetor de flags para identificar os nos visitados
    /// @param traverse Vetor com os resultados da busca
    void bfsComponent(int node, vector<bool>& visited, vector<int>& traverse);

    /// @brief Funcao que realiza uma DFS (Depth First Search) (Recursiva) em um componente.
    /// @param node Numero do no na qual a a busca sera iniciada
    /// @param visited Vetor de flags para identificar os nos visitados
    /// @param traverse Vetor com os resultados da busca
    void dfsComponent(int node, vector<bool>& visited, vector<int>& traverse);

    /// @brief Funcao que realiza uma DFS Topologica (Recursiva) em um componente.
    /// @param node Numero do no na qual a a busca sera iniciada
    /// @param visited Vetor de flags para identificar os nos visitados
    /// @param traverse Vetor com os resultados da busca
    void topologicDfsComponent(int node, vector<bool>& visited, vector<int>& traverse);

    /// @brief Busca DFS especial que usa EdgeTable transposta no lugar da original do grafo
    /// @param node Numero do no na qual a a busca sera iniciada
    /// @param transposed EdgeTable transposta (com direcoes invertidas) para o algoritmo de Kosaraju
    /// @param visited Vetor de flags para identificar os nos visitados
    /// @param component Vetor com a componente fortemente conexa encontrada
    void kosarajuDfs(int node, const EdgeTable& transposed, vector<bool>& visited, vector<int>& component);

    /// @brief Transpoe a EdgeTable do grafo para uso do Kosaraju
    /// @return Uma EdgeTable transposta
    EdgeTable transpose();

    public:
    
    Graph(bool isOriented, int nodeCount, EdgeTable edges) 
    : isOriented(isOriented), nodeCount(nodeCount), edges(edges) {}

    int getNodeCount(){return nodeCount;}

    /// @brief Cria um arquivo .dot para a visualizacao do grafo.
    /// @param filename nome do arquivo (origem)
    /// @return valor booleano que diz se a criacao foi feita com sucesso.
    bool createDotFile(const string& filename);

    /// @brief Cria um arquivo .dot para a visualizacao do grafo com highlighting dos componentes diferentes.
    /// @param filename nome do arquivo (origem)
    /// @param components o vetor de componentes
    /// @return valor booleano que diz se a criacao foi feita com sucesso.
    bool createDotFileKosaraju(const string& filename, const Components& components);

    /// @brief Cria um arquivo .dot para a visualizacao do grafo com highlighting da AGM.
    /// @param filename nome do arquivo (origem)
    /// @param treeEdges as ligacoes da arvore AGM.
    /// @return valor booleano que diz se a criacao foi feita com sucesso.
    bool createDotFileKruskal(const string& filename, const TreeEdges& treeEdges);

    
    /// @brief Funcao que realiza uma busca BFS por todo o grafo.
    /// @param origin O no de origem para o inicio do algoritmo
    /// @return o vetor de resultados da busca (caminho gerado)
    vector<int> bfs(int origin);

    /// @brief Funcao que realiza uma busca DFS por todo o grafo.
    /// @param origin O no de origem para o inicio do algoritmo
    /// @return o vetor de resultados da busca (caminho gerado)
    vector<int> dfs(int origin);

    /// @brief Funcao que realiza uma busca de ordenacao topologica por todo o grafo.
    /// @param origin O no de origem para o inicio do algoritmo
    /// @return o vetor de resultados da busca (caminho gerado)
    vector<int> topologicOrder(int origin);

    /// @brief Funcao que realiza o algoritmo de kosaraju.
    /// @return retorna os componentes em um vector<vector<int>>
    Components kosaraju();

    /// @brief Funcao que realiza o algoritmo de Dijkstra.
    /// @param origin no de origem para o algoritmo
    /// @return retorna as distancias do no de origem por um vector<int>
    vector<int> dijkstra(int origin);

    /// @brief Funcao que realiza o algoritmo de Kruskal para geracao da AGM.
    /// @return Retorna um pair com o peso total da AGM e as ligacoes dela (TreeEdges)
    pair<int, TreeEdges> kruskal();
};

/// @brief Função que le um arquivo de texto no formato e local especificados
/// @param filename o nome do arquivo de texto de input
/// @return retorna um ponteiro para um novo grafo criado
Graph* readGraph(string filename);

#endif