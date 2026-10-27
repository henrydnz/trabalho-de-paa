#include "menu.hpp"
#include <iomanip> // Adicionado para formatação da tabela

using namespace std;

void printPath(const vector<int>& v) {
    for (size_t i = 0; i < v.size(); i++) cout << v[i] << (i + 1 == v.size() ? "" : "-");
    cout << endl;
}

void pauseMenu() {
    cout << "\n[Enter p/ continuar...]";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get(); 
}

void menuAlgorithms(Graph* g, string name) {
    int option;
    do {
        cout << "\n========== MENU DE ALGORITMOS ==========\n";
        cout << "1. Busca em profundidade (DFS)\n";
        cout << "2. Busca em largura (BFS)\n";
        cout << "3. Ordenacao topologica\n";
        cout << "4. Componentes fortemente conexas (Kosaraju)\n";
        cout << "5. Dijkstra\n";
        cout << "6. Kruskal\n";
        cout << "7. Carregar novo grafo\n";
        cout << "8. Sair do programa\n";
        cout << "========================================\n";
        cout << "Escolha uma opcao: ";
        
        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[ERRO] Entrada invalida. Digite um numero.\n";
            pauseMenu();
            continue;
        }

        int origin = -1;
        vector<int> res;
        Components ans;

        switch(option) {
            case 1:
                cout << "Digite o vertice de origem para a Busca em Profundidade (DFS): ";
                cin >> origin;
                if(origin >= 0 && origin < g->getNodeCount()) {
                    res = g->dfs(origin);
                    cout << "Saida DFS: ";
                    printPath(res);
                } else cout << "[ERRO] Vertice de origem invalido.\n";
                pauseMenu();
                break;
                
            case 2:
                cout << "Digite o vertice de origem para a Busca em Largura (BFS): ";
                cin >> origin;
                if(origin >= 0 && origin < g->getNodeCount()) {
                    res = g->bfs(origin);
                    cout << "Saida BFS: ";
                    printPath(res);
                } else cout << "[ERRO] Vertice de origem invalido.\n";
                pauseMenu();
                break;
                
            case 3:
                cout << "Digite o vertice de origem para a Ordenacao Topologica: ";
                cin >> origin;
                if(origin >= 0 && origin < g->getNodeCount()) {
                    res = g->topologicOrder(origin);
                    cout << "Saida Ordenacao Topologica: ";
                    printPath(res);
                } else cout << "[ERRO] Vertice de origem invalido.\n";
                pauseMenu();
                break;
                
            case 4: 
                cout << "Digite o vertice de origem para Componentes Fortemente Conexas (Kosaraju): ";
                cin >> origin;
                if(origin >= 0 && origin < g->getNodeCount()) {
                    ans = g->kosaraju(origin);
                    if (!ans.empty()) {
                        for (size_t i = 0; i < ans.size(); i++) {
                            cout << "Componente " << i + 1 << ": ";
                            for (size_t j = 0; j < ans[i].size(); j++) {
                                cout << ans[i][j] << (j + 1 == ans[i].size() ? "" : ", ");
                            }
                            cout << endl;
                        }
                        if(g->createDotFileKosaraju(ans)){
                            string inName = DOTFILE_PATH_KOSARAJU + name;
                            string outName = VIEWPNGFILE_PATH_KOSARAJU + name;
                            getGraphView(inName, outName);
                        }
                    }
                } else cout << "[ERRO] Vertice de origem invalido.\n";
                pauseMenu();
                break;
                
            case 5: 
                cout << "Digite o vertice de origem para o algoritmo de Dijkstra: ";
                cin >> origin;
                if(origin >= 0 && origin < g->getNodeCount()) {
                    res = g->dijkstra(origin);
                    if(!res.empty()){
                        cout << left << setw(5) << "no" << "|   distancia\n";
                        for(int i = 0; i < g->getNodeCount(); i++){
                            cout << left << setw(5) << i << "|   " << res[i] << "\n";
                        }
                    }
                } else cout << "[ERRO] Vertice de origem invalido.\n";
                pauseMenu();
                break;
                
            case 6:
                cout << "Digite o vertice de origem para o algoritmo de Kruskal: ";
                cin >> origin;
                if(origin >= 0 && origin < g->getNodeCount()) {
                    pair<int, TreeEdges> kruskalRes = g->kruskal(origin);
                    TreeEdges treeEdges = kruskalRes.second;
                    
                    cout << "peso total: " << kruskalRes.first << endl;
                    cout << "arestas: ";
                    for(int i=0;i<treeEdges.size();i++){
                        for(int n : treeEdges[i]){
                            cout << "(" << i << ", " << n << ") ";
                        }
                    }
                    if(g->createDotFileKruskal(treeEdges)){     
                        string inName = DOTFILE_PATH_KRUSKAL + name;
                        string outName = VIEWPNGFILE_PATH_KRUSKAL + name;
                        getGraphView(inName, outName);
                    }
                } else cout << "[ERRO] Vertice de origem invalido.\n";
                pauseMenu();
                break;
                
            case 7:
                cout << "Voltando ao menu de carregamento...\n";
                return;
                
            case 8:
                cout << "Encerrando o software...\n";
                exit(0);
                
            default:
                cout << "[ERRO] Opcao invalida.\n";
                pauseMenu();
        }
    } while (true);
}

void runMenu() {
    while (true) {
        logsUtil.resetLog();
        
        cout << "\n========== MENU PRINCIPAL ==========\n";
        cout << "1. Carregar grafo\n";
        cout << "2. Sair\n";
        cout << "Escolha uma opcao: ";
        
        int opt;
        cin >> opt;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Digite 1 ou 2.\n";
            continue;
        }

        if (opt == 1) {
            string filename;
            cout << "Digite o nome do arquivo do grafo (precisa estar em \\input): ";
            cin >> filename;
            
            Graph* g = readGraph("..\\input\\" + filename);
            if (g) {
                cout << "\nGrafo carregado com sucesso!\n";
                string inName = DOTFILE_PATH + filename;
                string outName = VIEWPNGFILE_PATH + filename;
                if(g->createDotFile()) getGraphView(inName, outName);
                pauseMenu();
                menuAlgorithms(g, filename);
                delete g;
            } else {
                cout << "[ERRO] Falha ao carregar o grafo. Verifique logs.\n";
                pauseMenu();
            }
        } else if (opt == 2){ 
            cout << "Encerrando o software...j\n"; 
            break;
        } else {
            cout << "[ERRO] Opcao invalida.\n"; 
            pauseMenu();
        }
    }
}