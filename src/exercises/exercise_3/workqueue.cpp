//
// Created by siera on 19/11/2023.
//

#include "workqueue.h"
#include <iostream>

/** Definição do problema
    ->Criar duas filas uma para engine workqueue e uma para clean workqueue.
    ->Cada uma das filas deve ser repesentada por uma thread separada.
    ->Tais threads devem executar de forma iterativa, verificando a flag de conclusão, que deve ser definida quando o usuario
    solicitar a parada através do console, inserindo o comando 100
    ->Cada thread deve verificar a fila conrrespondete em busca de trabalho.
    ->Se a thread em execução encontrar algum comando na fila correspondente, ela deve executar o comando e dormir por um segundo.
    ->Se não houver comandos, as threads devem dormir por dois segundos.
    ->O capitão (main) não precisa esperar que um comando termine, e ele deve passar pelo menos um segundo entre dois comandos.
*/

int main() {
    std::queue<int> cleanWork;
    std::queue<int> engineWork;
    int choice;
    int cleanWorkLenght = 0;
    int engineWorkLenght = 0;
    std::thread threadCleanWork(cleanWorkFunctions, std::ref(cleanWork), std::ref(cleanWorkLenght));
    std::thread threadEngineWork(engineWorkFunctions, std::ref(engineWork), std::ref(engineWorkLenght));
    int choiceWork;
    while (true) {
        std::cout << "CHOICE WORK:\n1-Clean work\n2-Engine works\n100-End works!\n" << std::endl;
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "Choice clean work\n"
                    "1-Clean\n"
                    "100-End work\n" << std::endl;
            std::cin >> choiceWork;
            if (choiceWork == 1) {
                cleanWorkLenght++;
                cleanWork.push(1);
            }
            if (choiceWork == 100) {
                cleanWorkLenght--;
                cleanWork.push(100);
            }
        }
        if (choice == 2) {
            std::cout << "Choice engine work\n"
                    "1-Full speed ahead\n"
                    "2-Stop ship\n"
                    "100-End work\n" << std::endl;
            std::cin >> choiceWork;
            if (choiceWork == 1) {
                engineWorkLenght++;
                engineWork.push(1);
            }
            if (choiceWork == 2) {
                engineWorkLenght++;
                engineWork.push(2);
            }
            if (choiceWork == 100) {
                engineWorkLenght--;
                engineWork.push(100);
            }
        }
        if (choice == 100) {
            break;
        }
    }
    threadCleanWork.join();
    threadEngineWork.join();
    return 0;
}
