//
// Created by siera on 03/12/2023.

#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <utility>


/**
 * \brief A classe bank_account é utilizada para representar contas bancarias.
 * Cada instancia de tal classe possui um saldo (balance), um nome (name), e um mutex (m) para garantir que
 * operações seguras em ambientes concorrentes.
 */
class bank_account {
    double balance;
    std::string name;
    std::mutex m;

public:
    bank_account() {
    };

    bank_account(double _balance, std::string _name) : balance(_balance), name(std::move(_name)) {
    }

    bank_account(const bank_account&);

    bank_account& operator=(const bank_account&) = delete;

    /**
     * \brief Retira uma certa quantia de salda da conta
     * \param amount valor a ser retirado da conta
     */
    void withdrow(const double amount) {
        std::lock_guard<std::mutex> lg(m);
        balance -= amount;
    }

    /**
     * \brief Adiciona uma certa quantia a conta
     * \param amount valor a ser adicionado a conta.
     */
    void deposite(const double amount) {
        std::lock_guard<std::mutex> lg(m);
        balance += amount;
    }

    /**
     * \brief Transfere uma quantia de uma conta para a outra conta.
     * \param from Conta bancararia que irá realizar a tranferencia.
     * \param to Conta bancaria que recebera a transferencia.
     * \param amount Quantidade de dinheiro que sera transferido.
     */
    void transfer(bank_account&from, bank_account&to, double amount) {
        std::lock_guard<std::mutex> lg_1(from.m); // Declara o primeiro mutex
        std::cout << "Lock for" << from.name << "account acquire by " << std::this_thread::get_id << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Dorme por 1 segundo

        std::cout << "Wait to acquire lock for " << to.name << " account by " << std::this_thread::get_id << std::endl;

        std::lock_guard<std::mutex> lg_2(to.m); // Declara o segundo mutex

        from.balance -= amount;
        to.balance += amount;
        std::cout << "Transfer to - " << to.name << " from - " << from.name << " end \n";
    }
};


#endif //BANK_ACCOUNT_H
