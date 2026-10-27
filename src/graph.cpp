#include "graph.hpp"

Graph* readGraph(string filename){
    ifstream file(filename);
    
    if(!file.is_open()){
        stringstream ss;
        ss << "Arquivo " << filename << "nao conseguiu ser aberto apra a leitura do grafo.\n" <<
        "Cheque se  o nome coincide, ou se o arquivo esta na mesma pasta.";
        cout << ss.str() << endl;
        logsUtil.log(ss.str(), 1);
    }
    
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

    logsUtil.log("Orientado: " + to_string(oriented));

    // second line
    getline(file, line);
    if(!regex_match(line, match, secondLine)){
        wrongInputFileFormat(2, "V=PosInt", line);
        return nullptr;
    }
    int nodeCount = stoi(match[1]);

    logsUtil.log("Num Vertices: " + to_string(nodeCount));

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
        
        if(origin >= nodeCount || dest >= nodeCount) {
            stringstream err; 
            err << "No origem ou destino invalidos ( linha " << lineCount << ").";
            logsUtil.log(err.str(), 1);
            return nullptr;
        }
        
        edgeTable[origin].push_back(Edge(dest,weight));
        logsUtil.log("Adicionou Vertice: (" + to_string(origin) + ", " + to_string(dest) + "), peso = " + to_string(weight));
        if(!oriented && origin != dest) edgeTable[dest].push_back(Edge(origin,weight));
    }

    logsUtil.log("Arquivo " + filename + " lido com sucesso.");
    
    return new Graph(oriented, nodeCount, edgeTable);
}

bool Graph::createDotFile(){
    ofstream dot(DOTFILE_PATH);
    if(!dot.is_open()){
        stringstream ss;
        ss << "Arquivo " << DOTFILE_PATH << " nao conseguiu ser aberto para a visualizacao do grafo.\n";
        logsUtil.log(ss.str(), 1);
        return false;
    }

    string name = isOriented ? "digraph" : "graph";
    string edge = isOriented ? " -> " : " -- ";

    dot << name << " G {\n";
    dot << "edge [color=gray]\n";
    for(int i=0;i<nodeCount;i++){
        for(Edge e:edges[i]){
            // no repeated edges on not oriented graphs
            if(isOriented || i <= e.dest){
                dot << i << edge << e.dest << " [label=\"" << e.weight << "\"];\n";
            }
        }
    }
    dot << "}";

    return true;
}

bool Graph::createDotFileKosaraju(Components& components){
    ofstream dot(DOTFILE_PATH_KOSARAJU);
    if(!dot.is_open()){
        stringstream ss;
        ss << "Arquivo " << DOTFILE_PATH_KOSARAJU << "nao conseguiu ser aberto para a visualizacao do grafo kosaraju.\n";
        cout << ss.str() << endl;
        logsUtil.log(ss.str(), 1);
        return false;
    }

    string name = isOriented ? "digraph" : "graph";
    string edge = isOriented ? " -> " : " -- ";

    vector<string> colors = {
        "red", "blue", "green", "orange", "purple",
        "cyan", "magenta", "gold", "brown", "deeppink"
    };

    dot << name << " G {\n";
    dot << "edge [color=gray]\n";
    for(int i=0;i<nodeCount;i++){
        for(Edge e:edges[i]){
            // no repeated edges on not oriented graphs
            if(isOriented || i <= e.dest){
                dot << i << edge << e.dest << " [label=\"" << e.weight << "\"";
                for(int j=0; j<components.size(); j++){
                    vector<int> component = components[j];

                    if(find(component.begin(),component.end(),i) != component.end() &&
                        find(component.begin(),component.end(),e.dest) != component.end()
                    ){
                        string color = colors[j%colors.size()];
                        dot << ", color=" << color << ", fontcolor=" << color;
                    }
                }
                dot << "];\n";
            }
        }
    }
    dot << "}";

    return true;
}

bool Graph::createDotFileKruskal(TreeEdges& treeEdges){
    ofstream dot(DOTFILE_PATH_KRUSKAL);
    if(!dot.is_open()){
        stringstream ss;
        ss << "Arquivo " << DOTFILE_PATH_KRUSKAL << "nao conseguiu ser aberto para a visualizacao do grafo kosaraju.\n";
        cout << ss.str() << endl;
        logsUtil.log(ss.str(), 1);
        return false;
    }

    string name = isOriented ? "digraph" : "graph";
    string edge = isOriented ? " -> " : " -- ";

    vector<string> colors = {
        "red", "blue", "green", "orange", "purple",
        "cyan", "magenta", "gold", "brown", "deeppink"
    };

    dot << name << " G {\n";
    dot << "edge [color=gray]\n";
    for(int i=0;i<nodeCount;i++){
        for(Edge e:edges[i]){
            // no repeated edges on not oriented graphs
            if(isOriented || i <= e.dest){
                dot << i << edge << e.dest << " [label=\"" << e.weight << "\"";
                for(int n : treeEdges[i]) if(n == e.dest) dot << ", color=red, fontcolor=red";
                dot << "];\n";
            }
        }
    }
    dot << "}";

    return true;
}

vector<int> Graph::search(int origin, void (Graph::*method)(int,vector<bool>&,vector<int>&), bool reverseAns){
    vector<int> traverse; vector<bool> visited (nodeCount, false);
    // apply method on origin node
    (this->*method)(origin, visited, traverse);
    // apply method on remaining components
    for(int i=0;i<nodeCount;i++) if(!visited[i]) (this->*method)(i, visited, traverse);
    
    if(reverseAns) reverse(traverse.begin(), traverse.end());
    return traverse;
};

void Graph::bfsComponent(int node, vector<bool>& visited, vector<int>& traverse){
    visited[node] = true;
    queue<int> q; q.push(node);
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
        if(!visited[v]) dfsComponent(v, visited, traverse);
    }
}

void Graph::topologicDfsComponent(int node, vector<bool>& visited, vector<int>& traverse){
    visited[node] = true;
    for(Edge e : edges[node]){
        int v = e.dest;
        if(!visited[v]) topologicDfsComponent(v, visited, traverse);
    }
    traverse.push_back(node);
}

static void logNodePath(vector<int>& path){
    stringstream ss;
    for (size_t i = 0; i < path.size(); i++) ss << path[i] << (i + 1 == path.size() ? "" : "-");
    logsUtil.log(ss.str());
}

vector<int> Graph::bfs(int origin){
    logsUtil.log("aplicando busca bfs... origem:"+to_string(origin));
    vector<int> path = search(origin, &Graph::bfsComponent, false);
    logNodePath(path);
    return path;
}
vector<int> Graph::dfs(int origin){
    logsUtil.log("aplicando busca dfs... origem:"+to_string(origin));
    vector<int> path = search(origin, &Graph::dfsComponent, false);
    logNodePath(path);
    return path;
}
vector<int> Graph::topologicOrder(int origin){
    logsUtil.log("aplicando ordenacao topologica... origem:"+to_string(origin));
    vector<int> path = search(origin, &Graph::topologicDfsComponent, true);
    logNodePath(path);
    return path;
}

Components Graph::kosaraju(int origin) {
    logsUtil.log("aplicando kosaraju... origem:"+to_string(origin));

    if(!isOriented){
        string err = "Grafo nao orientado nao pode ser analisado por kosaraju";
        cout << err << endl;
        logsUtil.log(err,1);
        return {};
    }

    vector<int> firstPass = topologicOrder(origin);

    EdgeTable transposed = transpose();

    Components ans;
    vector<bool> visited(nodeCount, false);

    for (int v : firstPass) {
        if (!visited[v]) {
            vector<int> component;
            kosarajuDfs(v, transposed, visited, component);
            sort(component.begin(), component.end());
            ans.push_back(component);
        }
    }
    sort(ans.begin(),ans.end(),[](const vector<int>&a,const vector<int>&b){return a.size()>b.size();});

    return ans;
}

EdgeTable Graph::transpose() {
    EdgeTable transposed(nodeCount);

    for (int u = 0; u < nodeCount; u++) {
        for (Edge e : edges[u]) {
            transposed[e.dest].push_back(Edge(u, e.weight));
        }
    }

    return transposed;
}

void Graph::kosarajuDfs(int node, const EdgeTable& transposed, vector<bool>& visited, vector<int>& component) {
    visited[node] = true;
    component.push_back(node);

    for (Edge e : transposed[node]) {
        if (!visited[e.dest]) {
            kosarajuDfs(e.dest, transposed, visited, component);
        }
    }
}

static bool hasNegativeWeights(int nodeCount, const EdgeTable& edges){
    logsUtil.log("procurando por pesos negativos...");
    for(int i=0;i<nodeCount;i++) for(Edge e : edges[i]) if(e.weight < 0) return true;
    logsUtil.log("grafo nao possui pesos negativos.");
    return false;
}

static void showDijkstraTable(vector<int>& res){
    vector<int> a(res.size());
    for(int i=0;i<res.size();i++) a[i]=i;
    logsUtil.log("nodes \\n dist:");
    logNodePath(a);
    logNodePath(res);
}

vector<int> Graph::dijkstra(int origin){
    logsUtil.log("aplicando dijkstra... origem:"+to_string(origin));
    if(hasNegativeWeights(nodeCount, edges)){
        string err = "Nao pode aplicar dijkstra em grafo com pesos negativos.";
        cerr << err << endl;
        logsUtil.log(err, 1);
        return {};
    }

    vector<int> dist (nodeCount, INT_INF);
    dist[origin] = 0;

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,origin});

    while(!pq.empty()){
        pair<int,int> p = pq.top(); pq.pop();
        int d = p.first; int u = p.second;

        if(d>dist[u]) continue;

        for(Edge e:edges[u]){
            int v = e.dest; int w = e.weight;

            int newDist = dist[u]+w;

            if(newDist<dist[v]){
                dist[v]=newDist;
                pq.push({newDist,v});
            }
        }
    }

    for(int& i:dist) if(i==INT_INF) i=-1;

    showDijkstraTable(dist);

    return dist;
}

vector<pair<int, Edge>> sortEdgesByWeight(EdgeTable& edges){
    logsUtil.log("ordenando vertices por peso");

    vector<pair<int, Edge>> sorted;

    for(int i = 0; i < edges.size(); i++){
        for(Edge e : edges[i]){ sorted.push_back({i, e}); }
    }

    sort(sorted.begin(),sorted.end(),[](const pair<int, Edge>& a, const pair<int, Edge>& b){return a.second.weight > b.second.weight;});

    return sorted;
}

static int _find(vector<int>& parent, int v){
    if(parent[v]!=v) parent[v]=_find(parent,parent[v]);
    return parent[v];
}

static void _union(vector<int>& parent, int u, int v){
    int rootu = _find(parent, u);
    int rootv = _find(parent, v);
    if(rootu != rootv) parent[rootu] = rootv;
}

pair<int, TreeEdges> Graph::kruskal(int origin){
    vector<int> parent(nodeCount);
    for(int i=0;i<nodeCount;i++) parent[i]=i;

    TreeEdges treeEdges (nodeCount);
    int count = 0;
    int totalWeight = 0;

    vector<pair<int, Edge>> sortedEdges = sortEdgesByWeight(edges);

    for(pair<int,Edge> e : sortedEdges){
        int u = e.first;
        int v = e.second.dest;
        int w = e.second.weight;

        if(_find(parent, u) != _find(parent, v)){
            _union(parent, u, v);
            treeEdges[u].push_back(v);
            totalWeight += w;
            count++;
        }

        if(count == nodeCount-1) break;
    }

    return {totalWeight, treeEdges};
}
