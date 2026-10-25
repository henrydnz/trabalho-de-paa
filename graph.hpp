#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
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

class Graph {
    private:

    vector<vector<Edge>> edges;
    int nodeCount;
    bool isOriented;

    void bfs_component(int node, vector<bool>& visited, vector<int>& traverse);
    void dfs_component(int node, vector<bool>& visited, vector<int>& traverse);

    public:

    Graph(bool isOriented, int nodeCount, EdgeTable edges) 
        : isOriented(isOriented), nodeCount(nodeCount), edges(edges) {}

    void showLog();

    vector<int> bfs(int origin);
    vector<int> dfs(int origin);
};

Graph* readGraph(string filename);

#endif