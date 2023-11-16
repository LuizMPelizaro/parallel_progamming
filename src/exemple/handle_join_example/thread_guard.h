//
// Created by siera on 14/11/2023.
//

#ifndef THREAD_GUARD_H
#define THREAD_GUARD_H
#include <thread>

class thread_guard {
    /**
     * \brief Declara um membro de dados privado, uma referência a um objeto
     */
    std::thread&t;


public:
    /**
     * \brief Construtor da classe recebe uma referência a uma thread e a armazena no membro de dados t
     * \param _t é a referencia a uma thread
     */
    explicit thread_guard(std::thread&_t) : t(_t) {

    }

    /**
     * \brief  O destrutor da classe.
     * Verifica se a thread é joinable (se pode ser unida) e a une se for o caso
     */
    ~thread_guard() {
        if (t.joinable()) {
            t.join();
        }
    }

    /**
     * \brief Estes são métodos excluídos, o que significa que a classe thread_guard não permite cópia ou atribuição.
     * Isso é feito para evitar situações confusas em que a mesma thread poderia ser gerenciada por múltiplos objetos thread_guard ao mesmo tempo.
     */
    thread_guard(const thread_guard&) = delete;

    thread_guard& operator=(const thread_guard&) = delete;
};
#endif //THREAD_GUARD_H
