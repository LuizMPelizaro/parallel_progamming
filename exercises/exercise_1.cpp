//
// Created by luiz- on 11/11/2023.
//
#include <iostream>
#include <thread>

/**
 * I want you launch 2 threads from main thread call thread A and thread B
 *
 * Thread A shoud execute a function called function A and B shoud execute function called function B
 *
 * From function A you have to launch anothre thread call thread C which will run thre funciton call test.
 * This test function shoud printout hello from test.
 *
 * Then I want you to order the thread in the order they are going to finish execution. First thread in the order shoud
 * be the first one to finish, lasted thread in the order shoud be las one to finish. Consider the main thread as well
 */


void function_test() {
    printf("Hello from test \n");

}

void function_a() {
    printf("Hello from A \n");
    std::thread threadC(function_test);
    threadC.join();

}

void function_b() {
    printf("Hello from B \n");
}

int main(int argc, char* argv[]) {
    printf("Init main thread ! \n");
    std::thread threadA(function_a);
    std::thread threadB(function_b);

    threadA.join();
    threadB.join();
    printf("Finish main thread !");
    return 0;
}
