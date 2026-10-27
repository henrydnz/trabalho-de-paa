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

typedef vector<vector<Edge>> EdgeTable;
typedef vector<vector<int>> Components;
typedef vector<vector<int>> TreeEdges;

class Graph {
    private:

    EdgeTable edges;
    int nodeCount;
    bool isOriented;

    /// @brief Funcao responsavel por distribuir uma busca no grafo, iniciando as recursoes 
    /// @param origin Numero do no onde a busca sera iniciada
    /// @param method Ponteiro para a funcao que sera realizada
    /// @param reverseAns Flaga para se a resposta precisa ser invertida (como na Topologica)
    /// @return Um vetor de inteiros com a resposta da funcao realizada
    vector<int> search(int origin, void (Graph::*method)(int,vector<bool>&,vector<int>&), bool reverseAns);
    
    // search functions (only on components)

    /// @brief Funcao que realiza uma BFS (Breadth First Search) (Recursiva)
    /// @param node Numero do no na qual a a busca sera iniciada
    /// @param visited Vetor de flags para identificar os nos visitados
    /// @param traverse Vetor com os resultados da busca
    void bfsComponent(int node, vector<bool>& visited, vector<int>& traverse);

    /// @brief Funcao que realiza uma DFS (Depth First Search) (Recursiva)
    /// @param node Numero do no na qual a a busca sera iniciada
    /// @param visited Vetor de flags para identificar os nos visitados
    /// @param traverse Vetor com os resultados da busca
    void dfsComponent(int node, vector<bool>& visited, vector<int>& traverse);

    /// @brief Funcao que realiza uma DFS Topologica (Recursiva)
    /// @param node Numero do no na qual a a busca sera iniciada
    /// @param visited Vetor de flags para identificar os nos visitados
    /// @param traverse Vetor com os resultados da busca
    void topologicDfsComponent(int node, vector<bool>& visited, vector<int>& traverse);

    
    // for kosaraju use

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


    bool createDotFile(string filename);
    bool createDotFileKosaraju(string filename, Components& components);
    bool createDotFileKruskal(string filename, TreeEdges& treeEdges);

    int getNodeCount(){return nodeCount;}
    
    // 
    vector<int> bfs(int origin);
    vector<int> dfs(int origin);
    vector<int> topologicOrder(int origin);
    Components kosaraju(int origin);
    vector<int> dijkstra(int origin);
    // not implemented
    pair<int, TreeEdges> kruskal(int origin);
};

Graph* readGraph(string filename);

#endif