//
// Created by Luiz on 02/12/2023.
//

#ifndef HELLO_MUTEX_H
#define HELLO_MUTEX_H
#include <algorithm>
#include <iostream>
#include <mutex>
#include <thread>
#include <list>

// Criação da lista
inline std::list<int> my_list;
// Criação do objeto mutex
inline std::mutex m;

inline void add_to_list(int const&x) {
    // Antes de adicionar um valor a lista bloqueamos o mutex , impedindo que outra thread acesse a lista durante a utilização dela por outra thread
    m.lock();
    my_list.push_front(x);
    // Ao terminar é importante desbloquear o mutex se não a outra thread nunca podera acessar essas funçoes porque a primeira
    // thread não a desbloqueou
    m.unlock();
}

inline void size() {
    m.lock();
    const int size = my_list.size();
    m.unlock();
    std::cout << "Size of the list is : " << size << std::endl;
}

inline void run() {
    std::thread thread_1(add_to_list, 4);
    std::thread thread_2(add_to_list, 11);
    std::thread thread_3(size);
    thread_1.join();
    thread_2.join();
}
#endif //HELLO_MUTEX_H
