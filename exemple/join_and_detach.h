//
// Created by siera on 13/11/2023.
//
#ifndef JOIN_AND_DETACH_H
#define JOIN_AND_DETACH_H

#include <iostream>
#include <thread>
#include <chrono>
/**
 *A chamada da função join introduz um ponto sincronizado entre a thread de lançamento e a thread que ela lançou,
 *e bloqueia a execução da thread que chama a função join até que a execução da thread lançada seja concluída.
 */

void foo() {
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    printf("Call foo function !\n");
}

void bar() {
    // sleep_for faz com que o progama espere 5 segundos.
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    printf("Call bar function !\n");
}

int run() {
    // Cria as threads
    std::thread foo_thread(foo);
    std::thread bar_thread(bar);

    // bar_thread é desanexada, o que significa que a função main não precisa de esperar ela terminar sua execução
    bar_thread.detach();
    printf("This is after bar thread detach  \n");

    // foo_thread é chamada, o que significa que a execução da função main ir aguarda até que ela termine sua execução
    foo_thread.join();
    printf("This is after bar thread join \n");
    return 0;
}
#endif // JOIN_AND_DETACH_H
