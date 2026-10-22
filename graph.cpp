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
    : isOriented(isOriented), nodeCount(nodeCount)
{
    for(int i = 0; i < nodeCount; i++)
        nodes.push_back(new GraphNode(i));

    makeLinks(edges);
}

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
        cerr << "Formatacao do arquivo errada na linha 1!" << endl;
        cerr << "Esperado: orientado=sim|nao.\n Lido: " << first_line << endl;
        return {};
    }

    oriented = (fl_match[1] == "sim") ? true : false;

    regex sl(R"(^V=([0-9]+)$)");
    smatch sl_match;

    int nodeCount;

    if(!regex_match(second_line, sl_match, sl)){
        cerr << "Formatacao do arquivo errada na linha 2!" << endl;
        cerr << "Esperado: V=inteiroPositivo.\n Lido: " << second_line << endl;
        return {};
    }

    nodeCount = stoi(sl_match[1]);

    regex edges(R"(^\(([0-9]+),([0-9]+)\)$)");
    smatch edge_match;

    string line;
    int lineCount = 3;

    vector<Edge> edges_list;

    while(getline(file, line)){
        if(!regex_match(line, edge_match, edges)){
            cerr << "Formatacao do arquivo errada na linha " << lineCount << "!" << endl;
            cerr << "Esperado: (inteiroPos,inteiroPos):inteiroPos\n Lido: " << line << endl;
            return {};
        }
        edges_list.push_back(Edge(stoi(edge_match[1]),stoi(edge_match[2]),stoi(edge_match[3])));
        lineCount++;
    }

    return new Graph(oriented, nodeCount, edges_list);
}