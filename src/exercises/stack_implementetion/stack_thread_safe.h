//
// Created by siera on 02/12/2023.
//

#ifndef STACK_THREAD_SAFE_H
#define STACK_THREAD_SAFE_H
#include <iostream>
#include <mutex>
#include <stack>
#include <thread>

template<typename T>
class stack_thread_safe {
    std::stack<T> stk;
    std::mutex m;

public:
    void push(T element) {
        std::lock_guard<std::mutex> lg(m);
        stk.push(element);
    }

    void pop() {
        std::lock_guard<std::mutex> lg(m);
        stk.pop();
    }

    T& top() {
        std::lock_guard<std::mutex> lg(m);
        return stk.top();
    }

    bool empty() {

    }

    size_t size() {

    }
};

#endif //STACK_THREAD_SAFE_H
