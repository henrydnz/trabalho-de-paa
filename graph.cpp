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

    regex pattern1(R"(^orientado=(sim|nao)$)");
    smatch fl_match;

    bool oriented;

    if(!regex_match(first_line, fl_match, pattern1)){
        cerr << "Formatacao do arquivo errada na linha 1!" << endl;
        cerr << "Esperado: orientado=sim|nao.\n Lido: " << first_line << endl;
        return {};
    }

    string op = fl_match[1];
    oriented = (op == "sim") ? true : false;

    std::regex pattern2(R"(^V=([0-9]+)$)");
    smatch sl_match;

    int nodeCount;

    if(!regex_match(second_line, sl_match, pattern2)){
        cerr << "Formatacao do arquivo errada na linha 2!" << endl;
        cerr << "Esperado: V=inteiroPositivo.\n Lido: " << second_line << endl;
        return {};
    }

    nodeCount = stoi(sl_match[1]);

    string line;
    while(getline(file, line)){
        line.substr(line.find('(') + 1, line.find(','));
    }
}