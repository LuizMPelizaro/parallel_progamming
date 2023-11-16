//
// Created by siera on 15/11/2023.
//

#ifndef CREW_MEBERS_H
#define CREW_MEBERS_H
#include <iostream>
#include <thread>

/*
 * Enunciado do exercicio:
 * Vamos considerar três papéis para esta implementação. Capitão, Equipe do Motor e Limpeza.
 * O Capitão será representado pela thread principal em seu programa.
 * O capitão pode dar três comandos.
 * --------
 * 1- Ele pode ordenar à equipe de limpeza que limpe, e o capitão não precisa esperar por esse comando até que esteja concluído.
 * 2,3- Os dois comandos seguintes são "full speed ahead" (velocidade máxima à frente) e "stop the engine" (parar o motor).
 * O capitão deve esperar até que a equipe do motor termine esses comandos para prosseguir com o próximo comando.
 * Qualquer outro comando no console deve imprimir comando invalido.
 * O comando de parada sera exit no meu caso.
*/
class crew_mebers {
public:
    static void funcionability(crew_mebers* instace,const int function) {
        switch (function) {
            case 0:
                exit(EXIT_SUCCESS);
                break;
            case 1: {
                std::thread clean_thread(&crew_mebers::clean,instace);
                clean_thread.detach();
                break;
            }
            case 2: {
                std::thread speed_up_thread(&crew_mebers::full_speed_ahead,instace);
                speed_up_thread.join();
                break;
            }
            case 3: {
                std::thread stop_boat_thread(&crew_mebers::stop_the_engine, instace);
                stop_boat_thread.join();
                break;
            }
            default:
                printf("Invalid function!\n");
                break;
        }
    }

private:
    static void clean() {
        printf("I'm cleaning !\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        printf("Clean compleat !\n");
    }

    static void full_speed_ahead() {
        printf("Speeding up !\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        printf("Full speed ahead !\n");
    }

    static void stop_the_engine() {
        printf("Slowing down !\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        printf("Stop compleat !\n");
    }
};


#endif //CREW_MEBERS_H
