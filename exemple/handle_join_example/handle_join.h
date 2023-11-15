//
// Created by siera on 14/11/2023.
//
#ifndef HANDLE_JOIN_H
#define HANDLE_JOIN_H

#include <iostream>
#include <thread>

#include "thread_guard.h"


void foo() {
    printf("From fuction foo\n");
}

void othe_function() {
    std::cout << "This is other operation \n";
    throw std::runtime_error("This is a runtime error");
}

void run() {
    std::thread foo_thread(foo);
    thread_guard tg(foo_thread);
    try {
        othe_function();
    }
    catch (...) {
    }
}
#endif // HANDLE_JOIN_H
