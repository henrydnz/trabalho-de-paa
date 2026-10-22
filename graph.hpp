#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>

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
        bool isOriented;
        int nodeCount;

        vector<GraphNode*> nodes;

        void makeLinks(vector<Edge> edges);

    public:
        Graph(bool isOriented, int nodeCount, vector<Edge> edges);
};

Graph* readGraph(string filename);

#endif