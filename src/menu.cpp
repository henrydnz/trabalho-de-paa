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

void menuAlgorithms(Graph* g, string filename) {
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
            cout << "Entrada invalida. Digite um numero.\n";
            pauseMenu();
            continue;
        }

        int origin = -1;
        vector<int> res;
        Components ans;

        switch(option) {
            case 1:
                cout << "Digite o vertice de origem para DFS: ";
                cin >> origin;
                if(origin >= 0 && origin < g->getNodeCount()) {
                    res = g->dfs(origin);
                    cout << "Saida DFS: ";
                    printPath(res);
                } else cout << "Vertice de origem invalido.\n";
                pauseMenu();
                break;
                
            case 2:
                cout << "Digite o vertice de origem para BFS: ";
                cin >> origin;
                if(origin >= 0 && origin < g->getNodeCount()) {
                    res = g->bfs(origin);
                    cout << "Saida BFS: ";
                    printPath(res);
                } else cout << "Vertice de origem invalido.\n";
                pauseMenu();
                break;
                
            case 3:
                cout << "Digite o vertice de origem para a Ordenacao Topologica: ";
                cin >> origin;
                if(origin >= 0 && origin < g->getNodeCount()) {
                    res = g->topologicOrder(origin);
                    cout << "Saida Ordenacao Topologica: ";
                    printPath(res);
                } else cout << "Vertice de origem invalido.\n";
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
                        if(g->createDotFileKosaraju(filename, ans)) getGraphView(filename + "_kosaraju");
                        else cout << "Erro na criacao da visualizacao. checar logs.";
                    }
                } else cout << "Vertice de origem invalido.\n";
                pauseMenu();
                break;
                
            case 5: 
                cout << "Digite o vertice de origem para Dijkstra: ";
                cin >> origin;
                if(origin >= 0 && origin < g->getNodeCount()) {
                    res = g->dijkstra(origin);
                    if(!res.empty()){
                        cout << left << setw(5) << "no" << "|   distancia\n";
                        for(int i = 0; i < g->getNodeCount(); i++){
                            cout << left << setw(5) << i << "|   " << res[i] << "\n";
                        }
                    }
                } else cout << "Vertice de origem invalido.\n";
                pauseMenu();
                break;
                
            case 6:
                cout << "Digite o vertice de origem para Kruskal: ";
                cin >> origin;
                if(origin >= 0 && origin < g->getNodeCount()) {
                    pair<int, TreeEdges> kruskalRes = g->kruskal();
                    TreeEdges treeEdges = kruskalRes.second;
                    
                    cout << "peso total: " << kruskalRes.first << endl;
                    cout << "arestas: ";
                    for(int i=0;i<treeEdges.size();i++) for(int n : treeEdges[i]) cout << "(" << i << ", " << n << ") "; cout << endl;
                    if(g->createDotFileKruskal(filename, treeEdges)) getGraphView(filename + "_kruskal");
                    else cout << "Erro na criacao da visualizacao. checar logs.";
                } else cout << "Vertice de origem invalido.\n";
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
            cout << "Digite o nome do arquivo do grafo (sem .txt): ";
            cin >> filename;
            
            Graph* g = readGraph("..\\input\\" + filename + ".txt");
            if (g) {
                cout << "\nGrafo carregado com sucesso!\n";
                if(g->createDotFile(filename)) getGraphView(filename);
                else cout << "Erro na criacao da visualizacao. checar logs.";
                pauseMenu();
                menuAlgorithms(g, filename);
                delete g;
            } else {
                cout << "[ERRO] Falha ao carregar o grafo. Verifique logs.\n";
                pauseMenu();
            }
        } else if (opt == 2){ 
            cout << "Encerrando o software...\n"; 
            break;
        } else {
            cout << "[ERRO] Opcao invalida.\n"; 
            pauseMenu();
        }
    }
}