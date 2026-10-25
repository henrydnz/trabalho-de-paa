#include "utils.hpp"
#include "graph.hpp"

int main(){
    logsUtil.resetLog();

    Graph* g = readGraph("test.txt");

    g->showLog();

    g->bfs(0);
    g->dfs(0);
    g->topologicOrder(0);
    g->dijkstra(0);
}