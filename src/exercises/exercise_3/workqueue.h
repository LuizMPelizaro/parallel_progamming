//
// Created by siera on 19/11/2023.
//

#ifndef WORKQUEUE_H
#define WORKQUEUE_H
#include <iostream>
#include <queue>
#include <thread>

/** Definição do problema
    ->Criar duas filas uma para engine workqueue e uma para clean workqueue.
    ->Cada uma das filas deve ser repesentada por uma thread separada.
    ->Tais threads devem executar de forma iterativa, verificando a flag de conclusão,
    que deve ser definida quando o usuario solicitar a parada através do console, inserindo o comando 100
    ->Cada thread deve verificar a fila conrrespondete em busca de trabalho.
    ->Se a thread em execução encontrar algum comando na fila correspondente, ela deve executar o comando e dormir por um segundo.
    ->Se não houver comandos, as threads devem dormir por dois segundos.
    ->O capitão (main) não precisa esperar que um comando termine, e ele deve passar pelo menos um segundo entre dois comandos.
*/


class workqueue {

public:
    void add_work(int value) {
        my_queue.push(value);
    }

    void work_concluid(int value) {
        my_queue.pop();
    }
private:
    std::queue<int> my_queue;
};


#endif //WORKQUEUE_H
