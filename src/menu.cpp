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

void menuAlgorithms(Graph* g) {
    int option;
    do {
        cout << "\n========== MENU DE ALGORITMOS ==========\n";
        cout << "1. Desenho de grafo\n";
        cout << "2. Busca em profundidade (DFS)\n";
        cout << "3. Busca em largura (BFS)\n";
        cout << "4. Ordenacao topologica\n";
        cout << "5. Componentes fortemente conexas (Kosaraju)\n";
        cout << "6. Dijkstra\n";
        cout << "7. Kruskal\n";
        cout << "8. Carregar novo grafo\n";
        cout << "9. Sair do programa\n";
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
                if(g->createDotFile()) getGraphView(DOTFILE_PATH, VIEWPNGFILE_PATH);
                pauseMenu();
                break;
                
            case 2:
                cout << "Digite o vertice de origem para a Busca em Profundidade (DFS): ";
                cin >> origin;
                if(origin >= 0 && origin < g->getNodeCount()) {
                    res = g->dfs(origin);
                    cout << "Saida DFS: ";
                    printPath(res);
                } else cout << "[ERRO] Vertice de origem invalido.\n";
                pauseMenu();
                break;
                
            case 3:
                cout << "Digite o vertice de origem para a Busca em Largura (BFS): ";
                cin >> origin;
                if(origin >= 0 && origin < g->getNodeCount()) {
                    res = g->bfs(origin);
                    cout << "Saida BFS: ";
                    printPath(res);
                } else cout << "[ERRO] Vertice de origem invalido.\n";
                pauseMenu();
                break;
                
            case 4:
                cout << "Digite o vertice de origem para a Ordenacao Topologica: ";
                cin >> origin;
                if(origin >= 0 && origin < g->getNodeCount()) {
                    res = g->topologicOrder(origin);
                    cout << "Saida Ordenacao Topologica: ";
                    printPath(res);
                } else cout << "[ERRO] Vertice de origem invalido.\n";
                pauseMenu();
                break;
                
            case 5: 
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
                    }
                } else cout << "[ERRO] Vertice de origem invalido.\n";
                pauseMenu();
                break;
                
            case 6: 
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
                
            case 7:
                cout << "nao imp.\n";
                pauseMenu();
                break;
                
            case 8:
                cout << "Voltando ao menu de carregamento...\n";
                return;
                
            case 9:
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
            string path;
            cout << "Digite o nome do arquivo do grafo (precisa estar em \input): ";
            cin >> path;
            
            Graph* g = readGraph("..\\input\\" + path);
            if (g) {
                cout << "\nGrafo carregado com sucesso!\n";
                g->showLog(); 
                pauseMenu();
                menuAlgorithms(g);
                delete g;
            } else {
                cout << "[ERRO] Falha ao carregar o grafo. Verifique o caminho e a formatacao do arquivo.\n";
                pauseMenu();
            }
        } else if (opt == 2) {
            cout << "Encerrando o software...\n"; break;
        } else {
            cout << "[ERRO] Opcao invalida.\n"; pauseMenu();
        }
    }
}