//
// Created by siera on 12/11/2023.
//
#ifndef JOIN_THREADS_H
#define JOIN_THREADS_H

#include <iostream>
#include <thread>

void test() {
    printf("Hello from test \n");
}

int run() {
    /*
     * LEMBRAR de que, para todas as threads joinables em seu programa, você deve chamar a função join ou detach.!!
     *
     * Agora, em um aplicativo trivial como este, chamar a função join pode não ter sentido além de fins de demonstração.
     *
     * Mas em aplicativos maiores que mantêm pools de threads, você definitivamente deve verificar se a thread específica
     * é joinable ou não antes de chamar a função join ou detach, pois a chamada de join ou detach para uma thread não
     * joinable resultaria em uma exceção, já que só podemos chamar join ou detach uma vez no ciclo de vida de uma thread.
     */
    std::thread thread1(test);
    if (thread1.joinable()) {
        printf("Thread 1 is joinable before join\n");
    }
    else {
        printf("Thread 1 is not joinable before join\n");
    }
    thread1.join();
    if (thread1.joinable()) {
        printf("Thread 1 is after before join\n");
    }
    else {
        printf("Thread 1 is not after before join\n");
    }

    /**
     *Para construir uma thread adequadamente, precisamos passar um objeto chamável como argumento para o construtor da classe de thread.
     *
     *E se esse objeto chamável receber parâmetros, você também precisa passar esses parâmetros corretamente.
     *Este objeto de construtor padrão não representa nenhuma thread ativa de execução. Portanto, ela não é joinable.
     */
    std::thread thread2;
    if (thread2.joinable()) {
        printf("Thread 2 is joinable");
    }
    else {
        printf("Thread 2 is not joinable");
    }

    /**
     *Ao construir uma thread sem associá-la a uma função, como no exemplo mencionado,
     * a thread não possui uma tarefa para executar e, portanto, não é joinable.
     * Tentar chamar join em uma thread que não é joinable resultará em um erro.
    */
    return 0;
}
#endif // JOIN_THREADS_H
