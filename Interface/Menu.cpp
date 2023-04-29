#include "Menu.h"

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
        /*
        else if (option == 2) // CHAMAR MÉTODO GRAFO
        else if (option == 3) // CHAMAR MÉTODO GRAFO
        else if (option == 4) // CHAMAR MÉTODO GRAFO
        */
        else if (option == 0) {
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
        "6 - Turismo\n\n" <<
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
            if (option >= 1 && option <= 6) break;
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
        } else if (option == 0) return;
    }
}
