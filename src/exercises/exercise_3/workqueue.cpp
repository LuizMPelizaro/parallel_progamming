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

int main(int argc, char* argv[]) {
    workqueue clean_queue;
    workqueue engine_queue;
    int exit = 1;
    int work = 0;
    printf("Choice work:\n1-Clean work \n2-Full speed\n3-Stop boat\n0-Exit\n100-Stop Work\n");
    while (exit != 0) {
        std::cin >> work;
        switch (work) {
            case 0:
                exit = 0;
            case 1:
                clean_queue.add_work(1);
                break;
            case 2:
                engine_queue.add_work(1);
                break;
            case 3:
                engine_queue.add_work(2);
                break;
            case 100:
                printf("Insert value to stop work\n5-Clean work\n6-Engine work");
                std::cin >> work;
                if (work == 5) {

                }
                if(work == 6) {

                }
            default:
                printf("Invalid work !");
        }
    }
    return 0;
}
