//
// Created by siera on 08/12/2023.
//

#include <iostream>
#include <mutex>
#include <ostream>
#include <thread>

std::mutex m1;
std::mutex m2;

void m1_frist_m2_second() {
    std::lock_guard<std::mutex> lg1(m1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "thread" << std::this_thread::get_id() << " has acquired lock for m1 mutex, its wait for m2" <<
            std::endl;
    std::lock_guard<std::mutex> lg2(m2);
    std::cout << "thread" << std::this_thread::get_id() << " has acquired lock for m2 mutex, its wait for m2" <<
            std::endl;
}

void m2_frist_m1_second() {
    std::lock_guard<std::mutex> lg1(m2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    std::cout << "thread" << std::this_thread::get_id() << " has acquired lock for m2 mutex, its wait for m2" <<
            std::endl;
    std::lock_guard<std::mutex> lg2(m1);
    std::cout << "thread" << std::this_thread::get_id() << " has acquired lock for m1 mutex, its wait for m2" <<
            std::endl;
}


int main(int argc, char* argv[]) {
    std::thread thread_1(m1_frist_m2_second);
    std::thread thread_2(m2_frist_m1_second);

    thread_1.join();
    thread_2.join();
}
