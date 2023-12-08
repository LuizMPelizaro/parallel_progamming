//
// Created by siera on 03/12/2023.
//

#include "bank_account.h"

int main(int argc, char* argv[]) {
    bank_account account;

    bank_account account_1(1000, "Josnei");
    bank_account account_2(2000, "Seu creyson");

    // O problema do dead lock acontece nas linhas abaixo quando a thread 1 e a thread 2 chamam a função transfer
    // ambas as threads ficam bloqueadas aguardando a liberação de um mutex qque a outra thread está segurando.

    std::thread thread_1(&bank_account::transfer, &account, std::ref(account_1), std::ref(account_2), 100);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread thread_2(&bank_account::transfer, &account, std::ref(account_2), std::ref(account_1), 100);

    thread_1.join();
    thread_2.join();
}
