#include "graph.hpp"

void Graph::makeLinks(vector<Edge> edges){
    for(int i = 0; i < nodeCount; i++){
        GraphNode* current = nodes.at(i);

        for(Edge e : edges){
            if(e.origin == i){
                current->links.push_back(Link(e.weight, e.dest));
            }
        }
    }
}


Graph::Graph(bool isOriented, int nodeCount, vector<Edge> edges) 
    : isOriented(isOriented), nodeCount(nodeCount), edges(edges)
{
    for(int i = 0; i < nodeCount; i++)
        nodes.push_back(new GraphNode(i));

    makeLinks(edges);
}

vector<int> Graph::bfs(int origin){
    vector<int> res;
    vector<bool> visited (nodeCount, false);

    queue<int> q;

    for(int i = 0; i < nodeCount; i++){
        if(visited[i]) continue;

        visited[i] = true;
        q.push(i);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            res.push_back(nodes[curr]->n);

            for (const Link& link : nodes[curr]->links) {
                int next = link.dest;

                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
    }

    return res;
}





// =================================================

Graph* readGraph(string filename){
    ifstream file = getFile(filename);

    string first_line;
    string second_line;

    getline(file, first_line);
    getline(file, second_line);

    regex fl(R"(^orientado=(sim|nao)$)");
    smatch fl_match;

    bool oriented;

    if(!regex_match(first_line, fl_match, fl)){
        logs_util.log("Formatacao do arquivo errada na linha 1!\nEsperado: orientado=sim|nao.\n Lido: " + first_line, 1);
        return {};
    }

    oriented = (fl_match[1] == "sim") ? true : false;

    regex sl(R"(^V=([0-9]+)$)");
    smatch sl_match;

    int nodeCount;

    if(!regex_match(second_line, sl_match, sl)){
        logs_util.log("Formatacao do arquivo errada na linha 2!\nEsperado: V=inteiro positivo.\n Lido: " + second_line, 1);
        return {};
    }

    nodeCount = stoi(sl_match[1]);

    regex edges(R"(^\(([0-9]+),([0-9]+)\):(-?[0-9]+)$)");
    smatch edge_match;

    string line;
    int lineCount = 3;

    vector<Edge> edges_list;

    while(getline(file, line)){

        if(!regex_match(line, edge_match, edges)){
            logs_util.log("Formatacao do arquivo errada na linha" + to_string(lineCount) + "!\nEsperado: orientado=sim|nao.\n Lido: " + line, 1);
            return {};
        }
        
        edges_list.push_back(Edge(stoi(edge_match[1]),stoi(edge_match[2]),stoi(edge_match[3])));
        lineCount++;
    }

    return new Graph(oriented, nodeCount, edges_list);
}