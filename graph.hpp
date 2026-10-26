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

class Graph {
    private:

    vector<vector<Edge>> edges;
    int nodeCount;
    bool isOriented;

    // distribute method function on all graph componentsk
    // method function structure: 
    //      void Graph::method(int node, vector<bool>& visited, vector<int>& traverse);
    vector<int> search(int origin, void (Graph::*method)(int,vector<bool>&,vector<int>&), bool reverseAns);
    
    // search functions (only on components)
    void bfsComponent(int node, vector<bool>& visited, vector<int>& traverse);
    void dfsComponent(int node, vector<bool>& visited, vector<int>& traverse);
    void topologicDfsComponent(int node, vector<bool>& visited, vector<int>& traverse);

    // for kosaraju use
    EdgeTable transpose();

    void kosarajuDfs(int node, const EdgeTable& transposed, vector<bool>& visited, vector<int>& component);
    public:
    
    Graph(bool isOriented, int nodeCount, EdgeTable edges) 
    : isOriented(isOriented), nodeCount(nodeCount), edges(edges) {}
    
    void showLog();

    bool createDotFile();

    int getNodeCount(){return nodeCount;}
    
    vector<int> bfs(int origin);
    vector<int> dfs(int origin);
    vector<int> topologicOrder(int origin);
    vector<vector<int>> kosaraju(int origin);
    vector<int> dijkstra(int origin);
};

Graph* readGraph(string filename);

#endif