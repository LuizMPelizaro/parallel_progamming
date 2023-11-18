//
// Created by siera on 18/11/2023.
//
#include <iostream>
#include <thread>

void loop_function(int&x) {
    while (true) {
        printf("Thread 1 value of X - %d\n", x);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}


int main(int argc, char* argv[]) {
    // No exemplo abaixa a main thread começa com o valor 9 e após 5 segundos tem o seu valor alteirado para 15
    int x = 9;
    printf("Main thread value of X - %d \n", x);

    // A função loop_function recebe uma referencia não um valor fixo isso causa um erro na compilação
    // Quando usamos referencia como parametro temos que utilizar o std::ref para indicar isso
    // std::thread thread_1(loop_function,x);

    // Abaixo referenciamos usando o std::ref para indicar o objeto de referencia
    std::thread thread_1(loop_function, std::ref(x));

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    x = 15;
    printf("Main thread value of X has been change to -%d \n", x);
    thread_1.join();
}
