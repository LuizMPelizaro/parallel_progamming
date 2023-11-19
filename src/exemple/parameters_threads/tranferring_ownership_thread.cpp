//
// Created by siera on 18/11/2023.
//

#include <thread>
#include <iostream>
//Explicação completa em https://www.notion.so/Parameters-to-threads-e71f2240a7e047d2a05d8742cfcd2825
void foo() {
    printf("Hello from foo\n");
}

void bar() {
    printf("Hello from bar\n");
}

int main(int argc, char* argv[]) {
    std::thread thread_1(foo);


    //Para copiar um thread e sua configuralção não é tão simples igual a implementação abaixo
    //std::thread thread_2 = thread_1;

    std::thread thread_2 = std::move(thread_1);

    thread_1 = std::thread(bar);
    std::thread thread_3(foo);

    thread_1 = std::move(thread_3);

    thread_1.join();
    thread_2.join();
    thread_3.join(); // Não é necessário, pois thread_3 não possui mais uma thread associada
}
