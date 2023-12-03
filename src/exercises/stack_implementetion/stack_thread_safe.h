//
// Created by siera on 02/12/2023.
//

#ifndef STACK_THREAD_SAFE_H
#define STACK_THREAD_SAFE_H
#include <iostream>
#include <memory>
#include <mutex>
#include <stack>

/**
 * @brief Uma pilha segura para threads que suporta operações push, pop, top, empty e size.
 * @tparam T Tipo dos elementos armazenados na pilha.
 */
template<typename T>
class stack_thread_safe {
    std::stack<std::shared_ptr<T>> stk; /**< Pilha que armazena ponteiros compartilhados para elementos do tipo T. */
    std::mutex m; /**< Mutex para garantir a sincronização ao acessar a pilha. */

public:
    /**
     * @brief Adiciona um elemento à pilha.
     * @param element Elemento a ser adicionado.
     */
    void push(T element) {
        std::lock_guard<std::mutex> lg(m);
        stk.push(std::make_shared<T>(element));
    }

    /**
     * @brief Remove e retorna o ponteiro compartilhado para o elemento no topo da pilha.
     * @return Ponteiro compartilhado para o elemento no topo da pilha.
     * @throws std::runtime_error se a pilha estiver vazia.
     */
    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lg(m);
        if (stk.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        std::shared_ptr<T> res(stk.top());
        stk.pop();
        return res;
    }

    /**
     * @brief Remove o elemento no topo da pilha e atribui seu valor a uma referência.
     * @param value Referência para armazenar o valor do elemento removido.
     * @throws std::runtime_error se a pilha estiver vazia.
     */
    void pop(T&value) {
        std::lock_guard<std::mutex> lg(m);
        if (stk.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        value = *(stk.top().get());
        stk.pop();
    }

    /**
     * @brief Retorna uma referência para o elemento no topo da pilha.
     * @return Referência para o elemento no topo da pilha.
     * @throws std::runtime_error se a pilha estiver vazia.
     */
    T& top() {
        std::lock_guard<std::mutex> lg(m);
        if (stk.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return *(stk.top());
    }

    /**
     * @brief Verifica se a pilha está vazia.
     * @return True se a pilha estiver vazia, false caso contrário.
     */
    bool empty() {
        std::lock_guard<std::mutex> lg(m);
        return stk.empty();
    }

    /**
     * @brief Retorna o tamanho atual da pilha.
     * @return Tamanho atual da pilha.
     */
    size_t size() {
        std::lock_guard<std::mutex> lg(m);
        return stk.size();
    }
};


#endif //STACK_THREAD_SAFE_H
