//
// Created by siera on 02/12/2023.
//
#include "stack_thread_safe.h"

#include <iostream>
#include <thread>
#include <vector>

int main() {
    // Criando uma instância da pilha thread-safe para inteiros
    stack_thread_safe<int> myStack;

    // Função para realizar operações de push e pop na pilha
    auto stackOperations = [&myStack](const int id) {
        for (int i = 0; i < 5; ++i) {
            myStack.push(id * 10 + i);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            try {
                int value;
                myStack.pop(value);
                std::cout << "Thread " << id << " popped: " << value << std::endl;
            } catch (const std::runtime_error& e) {
                std::cout << "Thread " << id << " exception: " << e.what() << std::endl;
            }
        }
    };

    // Criando threads para realizar operações na pilha
    std::vector<std::thread> threads;
    threads.reserve(3);
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(stackOperations, i); // emplace_back é utilizada para adicionar um novo elemento no final de um contêine
    }

    // Aguardando todas as threads terminarem
    for (auto& thread : threads) {
        thread.join();
    }

    // Imprimindo o estado final da pilha
    std::cout << "Final Stack Size: " << myStack.size() << std::endl;
    while (!myStack.empty()) {
        try {
            const int value = myStack.top();
            std::cout << "Final Stack Top: " << value << std::endl;
            myStack.pop();
        } catch (const std::runtime_error& e) {
            std::cout << "Final Stack Exception: " << e.what() << std::endl;
        }
    }

    return 0;
}
