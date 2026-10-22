#include "utils.hpp"
#include "graph.hpp"

int main(){
    Graph* g = readGraph("test.txt");

    logs_util.log("informacoes do grafo lido:");
    logs_util.log("orientado = "+(g->isOriented)?"sim":"nao");
    logs_util.log("v = "+to_string(g->nodeCount));
    logs_util.log("ligacoes:");

    for(GraphNode* node : g->nodes)
        for(Link l : node->links) 
            logs_util.log(to_string(node->n) + " -> " + to_string(l.dest) + " (w=" + to_string(l.weight) + ")");
    
}