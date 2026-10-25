#include "utils.hpp"
#include "graph.hpp"

int main(){
    logsUtil.resetLog();

    Graph* g = readGraph("test.txt");

    g->showLog();

    g->search(0, &Graph::bfs, "bfs");
    g->search(0, &Graph::dfs, "dfs");
    g->search(0, &Graph::topologicDfs, "ordenacao topologica", 1);
}