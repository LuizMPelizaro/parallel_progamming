//
// Created by siera on 15/11/2023.
//

#ifndef EXERCISE_1_H
#define EXERCISE_1_H

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

void run(){
    printf("Init main thread ! \n");
    std::thread threadA(function_a);
    std::thread threadB(function_b);

    threadA.join();
    threadB.join();
    printf("Finish main thread !");
    return 0;
}
#endif //EXERCISE_1_H
