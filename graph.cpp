#include "graph.hpp"

Graph* readGraph(string filename){
    ifstream file(filename);
    if(!file.is_open())
        logsUtil.log("Arquivo " + filename + " nao conseguiu ser aberto para a leitura do grafo.\n" +
            "Cheque se o nome coincide, ou se o arquivo esta na mesma pasta.", 1);
    
    string line;
    smatch match;

    regex firstLine(REGEX_INPUT_FILE_FIRST_LINE);
    regex secondLine(REGEX_INPUT_FILE_SECOND_LINE);
    regex edges(REGEX_INPUT_FILE_EDGES);
    
    // first line
    getline(file, line);
    if(!regex_match(line, match, firstLine)){
        wrongInputFileFormat(1, "orientado=sim|nao", line);
        return nullptr;
    }
    bool oriented = (match[1] == "sim") ? true : false;

    // second line
    getline(file, line);
    if(!regex_match(line, match, secondLine)){
        wrongInputFileFormat(2, "V=PosInt", line);
        return nullptr;
    }
    int nodeCount = stoi(match[1]);

    // third line (edges)
    EdgeTable edgeTable (nodeCount);
    for(int lineCount=3; getline(file, line); lineCount++){
        if(!regex_match(line, match, edges)){
            wrongInputFileFormat(lineCount, "(PosInt,PosInt):Int", line);
            return nullptr;
        }

        int origin = stoi(match[1]);
        int dest =   stoi(match[2]);
        int weight = stoi(match[3]);

        edgeTable[origin].push_back(Edge(dest,weight));
    }

    logsUtil.log("Arquivo " + filename + " lido com sucesso.");
    
    return new Graph(oriented, nodeCount, edgeTable);
}

void Graph::showLog(){
    logsUtil.log("\n===== Informacoes do Grafo =====\n", 3);

    logsUtil.log("Orientado: " + to_string(isOriented), 3);
    logsUtil.log("Num Vertices: " + to_string(nodeCount), 3);

    for(int i=0;i<nodeCount;i++)
        for(Edge l : edges[i])
            logsUtil.log(to_string(i) + " -- " + to_string(l.dest) + " | w = " + to_string(l.weight), 3);

    logsUtil.log("\n=================================\n", 3);
}

vector<int> Graph::search(int origin, void (Graph::*method)(int,vector<bool>&,vector<int>&), bool reverseAns){
    vector<int> traverse;
    vector<bool> visited (nodeCount, false);
    
    (this->*method)(origin, visited, traverse);
    
    for(int i=0;i<nodeCount;i++)
        if(!visited[i])
            (this->*method)(i, visited, traverse);
    
    if(reverseAns) reverse(traverse.begin(), traverse.end());

    logsUtil.log("resultado:");

    stringstream ss;
    for(int n:traverse) ss << n << " ";
    logsUtil.log(ss.str()+'\n');

    return traverse;
};

void Graph::bfsComponent(int node, vector<bool>& visited, vector<int>& traverse){
    visited[node] = true;

    queue<int> q;

    q.push(node);

    while(!q.empty()){
        int u = q.front(); q.pop();
        traverse.push_back(u);
        for(Edge e : edges[u]){
            int v = e.dest;
            if(!visited[v]){
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

void Graph::dfsComponent(int node, vector<bool>& visited, vector<int>& traverse){
    visited[node] = true;
    
    traverse.push_back(node);

    for(Edge e : edges[node]){
        int v = e.dest;
        if(!visited[v]) 
            dfsComponent(v, visited, traverse);
    }
}

void Graph::topologicDfsComponent(int node, vector<bool>& visited, vector<int>& traverse){
    visited[node] = true;

    for(Edge e : edges[node]){
        int v = e.dest;
        if(!visited[v]) 
            topologicDfsComponent(v, visited, traverse);
    }

    traverse.push_back(node);
}

vector<int> Graph::bfs(int origin){
    logsUtil.log("aplicando busca bfs");
    return search(origin, &Graph::bfsComponent, false);
}
vector<int> Graph::dfs(int origin){
    logsUtil.log("aplicando busca dfs");
    return search(origin, &Graph::dfsComponent, false);
}
vector<int> Graph::topologicOrder(int origin){
    logsUtil.log("aplicando ordenacao topologica");
    return search(origin, &Graph::topologicDfsComponent, true);
}

static bool hasNegativeWeights(int nodeCount, vector<vector<Edge>> edges){
    for(int i=0;i<nodeCount;i++) 
        for(Edge e : edges[i])
            if(e.weight < 0) return true;
    return false;
}

vector<int> Graph::dijkstra(int origin){
    logsUtil.log("aplicando dijkstra");
    if(hasNegativeWeights(nodeCount, edges)){
        string err = "Nao pode aplicar dijkstra em grafo com pesos negativos.";
        cerr << err << endl;
        logsUtil.log(err, 1);
        return {};
    }

    vector<int> dist (nodeCount, INFTY);

    dist[origin] = 0;

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

    pq.push({0,origin});

    while(!pq.empty()){
        pair<int,int> p = pq.top(); pq.pop();

        int d = p.first;
        int u = p.second;

        if(d>dist[u]) continue;

        for(Edge e:edges[u]){
            int v = e.dest;
            int w = e.weight;

            int newDist = dist[u]+w;

            if(newDist<dist[v]){
                dist[v] = newDist;
                pq.push({newDist,v});
            }
        }
    }

    return dist;
}

// =================================================

