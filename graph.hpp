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

    
    public:
    
    Graph(bool isOriented, int nodeCount, EdgeTable edges) 
    : isOriented(isOriented), nodeCount(nodeCount), edges(edges) {}
    
    void showLog();
    
    //distribute function method on all graph components
    vector<int> search(int origin, void (Graph::*method)(int,vector<bool>&,vector<int>&));

    //functions work only on component
    void bfs(int node, vector<bool>& visited, vector<int>& traverse);
    void dfs(int node, vector<bool>& visited, vector<int>& traverse);
};

Graph* readGraph(string filename);

#endif