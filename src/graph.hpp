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

    // distribute method function on all graph componentsk
    // method function structure: 
    //      void Graph::method(int node, vector<bool>& visited, vector<int>& traverse);
    vector<int> search(int origin, void (Graph::*method)(int,vector<bool>&,vector<int>&), bool reverseAns);
    
    // search functions (only on components)
    void bfsComponent(int node, vector<bool>& visited, vector<int>& traverse);
    void dfsComponent(int node, vector<bool>& visited, vector<int>& traverse);
    void topologicDfsComponent(int node, vector<bool>& visited, vector<int>& traverse);

    
    // for kosaraju use
    void kosarajuDfs(int node, const EdgeTable& transposed, vector<bool>& visited, vector<int>& component);
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