#include "Menu.h"
#include "../Classes/tsp.h"

Menu::Menu() {
    Graph g;
    this->graph = g;
}

void Menu::mainMenu() {
    while (true) {
        std::cout << "\nEscolha uma opção, escrevendo o número correspondente e pressionando ENTER\n" <<
        "1 - Carregar um grafo (leitura e parsing dos dados)\n";
        if (ready) {
            std::cout << "2 - Força bruta com backtracking\n" <<
            "3 - Aproximação triangular\n"
            "4 - Outra heurística\n";
        } else std::cout << "\nAs restantes opções apenas ficarão disponíveis quando carregar um grafo.\n";

        std::cout << "\n0 - Sair do programa" << std::endl;

        std::string input;
        int option;

        while (true) {
            std::getline(std::cin, input);
            try {
                option = stoi(input);
            } catch (std::invalid_argument) {
                option = -1;
            }
            std::cout << "\n";
            if (ready && option >= 2 && option <= 4) break;
            else if (option == 0 || option == 1) break;
            else std::cout << "Opção inválida. Por favor tente novamente.\n\n";
        }

        if (option == 1) readDataMenu();
        else if (option == 2) {
            auto start = std::chrono::high_resolution_clock::now();

            unsigned int path[graph.getVertexSet().size()];

            std::cout << "Custo: " << graph.tspBacktracking(path) << std::endl;

            auto stop = std::chrono::high_resolution_clock::now();

            for (size_t i = 0; i < graph.getVertexSet().size() - 1; i++)
                std::cout << path[i] << " -> ";
            std::cout << path[graph.getVertexSet().size()-1] << std::endl;

            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

            std::cout << "Tamanho do input: " << graph.getVertexSet().size() << std::endl;
            std::cout << "Tempo de execução: " << duration.count() << " ms" << std::endl;
        } else if (option == 3) {
            auto start = std::chrono::high_resolution_clock::now();

            // CHAMAR MÉTODO GRAFO
            std::cout << "Distância:" << " ";
            std::cout << tspApproximation(graph) << std::endl;

            auto stop = std::chrono::high_resolution_clock::now();

            // mostrar caminho?
            std::vector<unsigned int> vec = tspMST(graph);

            std::cout << "Caminho:" << " ";
            std::cout << "0" << " -> ";
            for (unsigned int i = 0; i < vec.size(); i++) {
                std::cout << vec[i] << " -> ";
            }
            std::cout << "0";

            std::cout << std::endl;

            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

            std::cout << "Tamanho do input: " << graph.getVertexSet().size() << std::endl;
            std::cout << "Tempo de execução: " << duration.count() << " ms" << std::endl;
        } else if (option == 4) {
            otherHeuristicMenu();
        }
        else if (option == 0) {
            //graph.print();
            std::cout << "Obrigado por usar o nosso programa!\n\nFrancisco Alves, Pedro Lima e Pedro Januário\n";
            return;
        }
    }
}

void Menu::readDataMenu() {
    while (true) {
        std::cout << "\nEscolha uma opção, escrevendo o número correspondente e pressionando ENTER\n\n\n" <<
        "Grafos Reais\n\n" <<
        "1 - Grafo 1 (1m nós, 500m arestas)\n" <<
        "2 - Grafo 2 (5m nós, 3M arestas)\n" <<
        "3 - Grafo 3 (10m nós, 10M arestas)\n\n\n" <<
        "Grafos de demonstração (toy)\n\n" <<
        "4 - Fretes (shipping)\n" <<
        "5 - Estádios\n" <<
        "6 - Turismo\n\n\n" <<
        "Grafos extra (completamente conexos)\n\n" <<
        "7 - 25 nós\n" <<
        "8 - 50 nós\n" <<
        "9 - 75 nós\n" <<
        "10 - 100 nós\n" <<
        "11 - 200 nós\n" <<
        "12 - 300 nós\n" <<
        "13 - 400 nós\n" <<
        "14 - 500 nós\n" <<
        "15 - 600 nós\n" <<
        "16 - 700 nós\n" <<
        "17 - 800 nós\n" <<
        "18 - 900 nós\n\n" <<
        "0 - Menu anterior\n\n";

        std::string input;
        int option;

        while (true) {
            std::getline(std::cin, input);
            try {
                option = stoi(input);
            } catch (std::invalid_argument) {
                option = -1;
            }
            std::cout << "\n";
            if (option >= 1 && option <= 18) break;
            else if (option == 0) return;
            else std::cout << "Opção inválida. Por favor tente novamente.\n\n";
        }

        if (option == 1) {
            readReal(1, graph);
            ready = true;
            return;
        } else if (option == 2) {
            readReal(2, graph);
            ready = true;
            return;
        } else if (option == 3) {
            readReal(3, graph);
            ready = true;
            return;
        } else if (option == 4) {
            readToy("shipping", graph);
            ready = true;
            return;
        } else if (option == 5) {
            readToy("stadiums", graph);
            ready = true;
            return;
        } else if (option == 6) {
            readToy("tourism", graph);
            ready = true;
            return;
        } else if (option == 7) {
            readExtra(25, graph);
            ready = true;
            return;
        } else if (option == 8) {
            readExtra(50, graph);
            ready = true;
            return;
        } else if (option == 9) {
            readExtra(75, graph);
            ready = true;
            return;
        } else if (option == 10) {
            readExtra(100, graph);
            ready = true;
            return;
        } else if (option == 11) {
            readExtra(200, graph);
            ready = true;
            return;
        } else if (option == 12) {
            readExtra(300, graph);
            ready = true;
            return;
        } else if (option == 13) {
            readExtra(400, graph);
            ready = true;
            return;
        } else if (option == 14) {
            readExtra(500, graph);
            ready = true;
            return;
        } else if (option == 15) {
            readExtra(600, graph);
            ready = true;
            return;
        } else if (option == 16) {
            readExtra(700, graph);
            ready = true;
            return;
        } else if (option == 17) {
            readExtra(800, graph);
            ready = true;
            return;
        } else if (option == 18) {
            readExtra(900, graph);
            ready = true;
            return;
        }
    }
}

void Menu::otherHeuristicMenu(){
    while (true) {
        std::queue<string> numbers;
        numbers.push("2");
        numbers.push("3");
        numbers.push("4");
        numbers.push("5");
        auto next_number = [&numbers]() {
            string front = numbers.front();
            numbers.pop();
            return front;
        };
        std::cout << "\nEscolha uma opção, escrevendo o número correspondente e pressionando ENTER\n\n" <<
                  "1 - Heurística 2-opt com restricao de apenas seguir as aresta do grafo" << std::endl <<
                  (graph.hasCoord ? next_number() + " - Heurística 2-opt sem restricao \n": "") <<
                  next_number() + " - Heurística 3-opt com restricao de apenas seguir as aresta do grafo" << std::endl <<
                  (graph.hasCoord ? next_number() + " - Heurística 3-opt sem restricao \n": "") <<
                  next_number() + " - " + (otherHeuristicPrintPath ? "Desabilitar a impressão do caminho" : "Habilitar a impressão do caminho") << std::endl <<
                  "0 - Menu anterior" << std::endl << std::endl;

        std::string input;
        int option;

        while (true) {
            std::getline(std::cin, input);
            try {
                option = stoi(input);
            } catch (std::invalid_argument) {
                option = -1;
            }
            std::cout << "\n";
            if (option >= 1 && option <= 6) break;
            else if (option == 0) return;
            else std::cout << "Opção inválida. Por favor tente novamente.\n\n";
        }

        if (option == 1) {
            run2Opt(true);
            return;
        } else if (option == 2 && graph.hasCoord) {
            run2Opt(false);
            return;
        } else if (option == 2 && !graph.hasCoord || option == 3 && graph.hasCoord) {
            run3Opt(true);
            return;
        } else if (option == 4 && graph.hasCoord) {
            run3Opt(false);
            return;
        } else if((option == 5 && graph.hasCoord) || (option == 3 && !graph.hasCoord)) {
            otherHeuristicPrintPath = !otherHeuristicPrintPath;
        }
    }
}

void Menu::run2Opt(bool withRestriction) {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Edge*> path;
    if(withRestriction)
        path = graph.RandomPath3();
    else
        path = graph.RandomPath4();
    if(path.empty()) {
        std::cout << "Não foi possível encontrar um caminho." << std::endl;
        return;
    }

    int size_before = 0;
    for (auto edge : path) {
        size_before += edge->getDist();
    }

    std::vector<Edge*> improvedPath;
    if(withRestriction)
        improvedPath  = improvePath(path, graph);
    else
        improvedPath  = improvePathAll(path, graph);

    int size_after = 0;
    for (auto edge : improvedPath) {
        size_after += edge->getDist();
    }

    auto stop = std::chrono::high_resolution_clock::now();

    if(otherHeuristicPrintPath)
        printPath("Caminho 2-opt: ", improvedPath);

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Custo inicial: " << size_before << std::endl;
    std::cout << "Custo final: " << size_after << std::endl;
    std::cout << "Melhoria: " << (float) (size_before - size_after) / size_before * 100 << "%" << std::endl;

    std::cout << "Tamanho do input: " << graph.getVertexSet().size() << std::endl;
    std::cout << "Tempo de execução: " << duration.count() << " ms" << std::endl;

    std::cout << "Pressione ENTER para continuar...";
    std::cin.ignore();
}

void Menu::run3Opt(bool withRestriction) {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Edge*> path;
    if(withRestriction)
        path = graph.RandomPath3();
    else
        path = graph.RandomPath4();
    if(path.empty()) {
        std::cout << "Não foi possível encontrar um caminho." << std::endl;
        return;
    }

    int size_before = 0;
    for (auto edge : path) {
        size_before += edge->getDist();
    }

    std::vector<Edge*> improvedPath;
    if(withRestriction)
        improvedPath  = improvePath3Opt(path, graph);
    else
        improvedPath  = improvePathAll3Opt(path, graph);

    int size_after = 0;
    for (auto edge : improvedPath) {
        size_after += edge->getDist();
    }

    auto stop = std::chrono::high_resolution_clock::now();

    if(otherHeuristicPrintPath)
        printPath("Caminho 3-opt: ", improvedPath);

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Custo inicial: " << size_before << std::endl;
    std::cout << "Custo final: " << size_after << std::endl;
    std::cout << "Melhoria: " << (float) (size_before - size_after) / size_before * 100 << "%" << std::endl;

    std::cout << "Tamanho do input: " << graph.getVertexSet().size() << std::endl;
    std::cout << "Tempo de execução: " << duration.count() << " ms" << std::endl;

    std::cout << "Pressione ENTER para continuar...";
    std::cin.ignore();
}
