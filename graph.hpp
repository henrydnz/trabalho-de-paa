#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <queue>

#include "utils.hpp"

using namespace std;

struct Edge {
    int origin;
    int dest;
    int weight;

    Edge(int o, int d, int w) : origin(o), dest(d), weight(w) {}
};

struct Link {
    int dest;
    int weight;

    Link(int w, int d) : weight(w), dest(d) {};
};

struct GraphNode {
    int n;
    vector<Link> links;

    GraphNode(int n) : n(n) {};
};

class Graph {
    private:
    
    
    
    void makeLinks(vector<Edge> edges);
    
    public:
        vector<GraphNode*> nodes;
        vector<Edge> edges; 
        int nodeCount;
        bool isOriented;
        Graph(bool isOriented, int nodeCount, vector<Edge> edges);

        vector<int> bfs(int origin);
};

Graph* readGraph(string filename);

#endif