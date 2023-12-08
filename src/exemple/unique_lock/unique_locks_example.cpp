//
// Created by siera on 08/12/2023.
//

#include "unique_locks_example.h"

int main(int argc, char* argv[]) {
    bank_account_refac account;

    bank_account_refac account_1(1000, "Josnei");
    bank_account_refac account_2(2000, "Seu creyson");


    std::thread thread_1(&bank_account_refac::transfer, &account, std::ref(account_1), std::ref(account_2), 100);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread thread_2(&bank_account_refac::transfer, &account, std::ref(account_2), std::ref(account_1), 100);

    thread_1.join();
    thread_2.join();
}
