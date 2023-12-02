//
// Created by siera on 02/12/2023.
//

#ifndef MUTEX_LOCK_GUARD_H
#define MUTEX_LOCK_GUARD_H
#include <iostream>
#include <list>
#include <mutex>
#include <thread>

inline std::list<int> my_list;
inline std::mutex m;

inline void add_to_list(int const&x) {
    //Quando um objeto "lock guard" é criado, ele tenta assumir a propriedade do mutex fornecido.
    //Quando o controle atual deixa o escopo no qual o objeto "lock guard" foi criado,
    //o "lock guard" será destruído e o mutex será liberado.
    std::lock_guard<std::mutex> lg(m);
    my_list.push_back(x);
}

inline void size() {
    std::lock_guard<std::mutex> lg(m);
    const int size = my_list.size();
    std::cout << "Size of the list is : " << size << std::endl;
}

inline void run() {
    std::thread thread_1(add_to_list, 4);
    std::thread thread_2(add_to_list, 11);
    std::thread thread_3(size);
    thread_1.join();
    thread_2.join();
}
#endif //MUTEX_LOCK_GUARD_H
