//
// Created by siera on 18/11/2023.
//

#include <iostream>
#include <thread>
#include <chrono>

// explicação completa sobre o codigo no link abaixo
// https://www.notion.so/Parameters-to-threads-e71f2240a7e047d2a05d8742cfcd2825

void func_2(int&x) {
    while (true) {
        try {
            std::cout << x << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        catch (...) {
            throw std::runtime_error("this is runtime error");
        }
    }
}

void func_1() {
    int x = 5;
    std::thread thread_2(func_2, std::ref(x));
    thread_2.detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "thread_1 finished execution \n";
}

int main(int argc, char* argv[]) {
    std::thread thread_1(func_1);
    thread_1.join();
}
