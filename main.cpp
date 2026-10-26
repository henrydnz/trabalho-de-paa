#include "utils.hpp"
#include "graph.hpp"

void logRes(vector<int> res){
    stringstream ss;
    for(int n : res) ss << n << " ";
    ss << endl;

    logsUtil.log(ss.str());
}

int main(){
    logsUtil.resetLog();

    string path = "test.txt";

    Graph* g = readGraph(path);
    if(!g){
        cerr << "Nao foi possivel ler o grafo no caminho " << path << endl << "Leia logs";
        return 0;
    }

    stringstream ss;
    vector<int> res;

    g->showLog();
    g->createDotFile();
    getGraphView();
    
    res=g->bfs(0);
    
    for(int n:res) ss << " -> " << n; ss << endl;
    logsUtil.log(ss.str()); ss.str("");

    res=g->dfs(0);

    for(int n:res) ss << " -> " << n; ss << endl;
    logsUtil.log(ss.str()); ss.str("");

    res=g->topologicOrder(0);

    for(int n:res) ss << " " << n; ss << endl;
    logsUtil.log(ss.str()); ss.str("");

    res=g->dijkstra(0);

    for(int i=0;i<g->getNodeCount();i++) ss << i << " | ";
    logsUtil.log(ss.str()); ss.str("");
    for(int n:res) ss << n << " | "; ss << endl;
    logsUtil.log(ss.str()); ss.str("");

    vector<vector<int>> ans;
    ans = g->kosaraju(0);

    for(vector<int> v:ans){
        ss << "Component: ";
        for(int n:v){
            ss << " " << n;
        }
        logsUtil.log(ss.str()); ss.str("");
    }
}