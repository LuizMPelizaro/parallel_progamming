//
// Created by siera on 19/11/2023.
//

#ifndef WORKQUEUE_H
#define WORKQUEUE_H
#include <iostream>
#include <queue>
#include <thread>
#include <chrono>

/** Definição do problema
    ->Criar duas filas uma para engine workqueue e uma para clean workqueue.
    ->Cada uma das filas deve ser repesentada por uma thread separada.
    ->Tais threads devem executar de forma iterativa, verificando a flag de conclusão,
    que deve ser definida quando o usuario solicitar a parada através do console, inserindo o comando 100
    ->Cada thread deve verificar a fila conrrespondete em busca de trabalho.
    ->Se a thread em execução encontrar algum comando na fila correspondente, ela deve executar o comando e dormir por um segundo.
    ->Se não houver comandos, as threads devem dormir por dois segundos.
    ->O capitão (main) não precisa esperar que um comando termine, e ele deve passar pelo menos um segundo entre dois comandos.
*/


inline void cleanWorkFunctions(std::queue<int>&work, const int&works) {
    printf("Clean work function start.\n");
    while (true) {
        if (!work.empty()) {
            printf("Clean work add in queue !\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            work.pop();
        }
        if (work.empty() and works == 0) {
            printf("No job in clean work queue !\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
        if (work.front() == 100) {
            printf("Clean work job is done !\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}

inline void engineWorkFunctions(std::queue<int>&works, const int&work) {
    printf("Engine work functions start.\n");
    while (true) {
        if (!works.empty()) {
            printf("Engine work add in queue !\n");
            if (works.front() == 1) {
                printf("Speeding up !\n");
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                printf("Full speed ahead !\n");
                works.pop();
            }
            if (works.front() == 2) {
                printf("Slowing dowm !\n");
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                printf("Stop compleat !\n");
                works.pop();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        if (works.empty() and work == 0) {
            printf("No job in engine work queue !\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
        if (works.front() == 100) {
            printf("Engine work job is done !\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}

#endif //WORKQUEUE_H
