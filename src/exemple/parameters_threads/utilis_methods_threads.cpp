//
// Created by siera on 18/11/2023.
//


#include <iostream>
#include <thread>
#include <chrono>

void foo() {
    std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
}

void get_ids() {
    std::thread thread_1(foo);
    std::thread thread_2(foo);
    std::thread thread_3(foo);
    std::thread thread_4;

    std::cout << "Thread_1 ID: " << thread_1.get_id() << std::endl;
    std::cout << "Thread_2 ID: " << thread_2.get_id() << std::endl;
    std::cout << "Thread_3 ID: " << thread_3.get_id() << std::endl;
    std::cout << "Thread_4 ID: " << thread_4.get_id() << std::endl;

    thread_1.join();
    thread_2.join();
    thread_3.join();

    std::cout << "Thread_1 ID: " << thread_1.get_id() << std::endl;
    std::cout << "Thread_2 ID: " << thread_2.get_id() << std::endl;
    std::cout << "Thread_3 ID: " << thread_3.get_id() << std::endl;
}

void wait() {
    using namespace std::chrono_literals;

    std::cout << "Hello waiter\n" << std::flush;

    const auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(2000ms);
    const auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();


    std::cout << "Waited " << elapsed << '\n';
}

int main(int argc, char* argv[]) {
    get_ids();
    wait();
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";
}


