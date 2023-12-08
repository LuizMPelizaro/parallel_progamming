//
// Created by siera on 08/12/2023.
//

#ifndef UNIQUE_LOCKS_EXAMPLE_H
#define UNIQUE_LOCKS_EXAMPLE_H
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <utility>


class bank_account_refac {
    double balance;
    std::string name;
    std::mutex m;

public:
    bank_account_refac() {
    };

    bank_account_refac(double _balance, std::string _name) : balance(_balance), name(std::move(_name)) {
    }

    bank_account_refac(const bank_account_refac&);

    bank_account_refac& operator=(const bank_account_refac&) = delete;

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
    void transfer(bank_account_refac&from, bank_account_refac&to, double amount) {
        std::cout << std::this_thread::get_id() << " hold the lock for both mutex \n";
        // O motivo o qual não ocorre deadlock no é po causa da utilização do unique lock com a opção do defer lock,
        // que adia a aquisição do bloqueio. Em seguida, a função lock é chamada para adquirir os bloqueios em ambas as
        // contas de forma simulânea. Isso evita a a possibilidade de deadlock, pois os bloqueios são adquiridos
        // em uma ordem expecifica, e essa ordem é seguida consistentamente em todas as chamadas a transfer
        std::unique_lock<std::mutex> ul_1(from.m, std::defer_lock);
        std::unique_lock<std::mutex> ul_2(to.m, std::defer_lock);
        std::lock(ul_1, ul_2);

        from.balance -= amount;
        to.balance += amount;
        std::cout << "transfer to - " << to.name << " from - " << from.name << " end \n";
    }
};


#endif //UNIQUE_LOCKS_EXAMPLE_H
