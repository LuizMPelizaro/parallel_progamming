//
// Created by siera on 25/11/2023.

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#define MIN_BLOCK_SIZE 1000


/**
 * \brief Faz o calculo dos elementos passados utilizando a função accumulate da lib numeric, e armazena o resultado
 * em uma referencia.
 * A primeira linha da função declara que ela é um template com dois parametros iterator e T o que possibilita que ela
 * trabalhe com multiplos tipos de iteratores e elementos.
 * \tparam iterator define o intervalo de elementos a serem somados.
 * \tparam T tipo de elemeto trabalhado ex int, float, doble e etc.
 * \param start Começo do intervalo.
 * \param end Final do intervalo
 * \param ref aonde o resltado é atribuido à referência.
 */
template<typename iterator, typename T>
void accumulate(iterator start, iterator end, T&ref) {
    static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");
    // Ela soma todos os elementos em um intervalo especificado e retorna o resultado. No código fornecido,
    // essa soma é atribuída à referência ref, permitindo que o resultado seja acessado fora da função.
    ref = std::accumulate(start, end, 0);
}


/**
 * \brief Realiza a acumulação paralela de elementos em um intervalo especificado.
 *
 * \tparam iterator Tipo do iterador usado para definir o intervalo de elementos.
 * \tparam T Tipo dos elementos a serem acumulados.
 *
 * \param start Iterador que aponta para o início do intervalo.
 * \param end Iterador que aponta para o final do intervalo (exclusivo).
 * \param ref Referência para o resultado final da acumulação.
 *
 * \return O resultado final da acumulação.
 *
 * A função divide o intervalo [start, end) em blocos e utiliza threads para
 * calcular a acumulação paralela desses blocos. O número de threads é ajustado
 * com base no tamanho do bloco e no número máximo de threads suportadas pelo hardware.
 * Os resultados parciais de cada thread são armazenados em um vetor e, em seguida,
 * somados para obter o resultado final.
 */
template<typename iterator, typename T>
T parallel_accumulate(iterator start, iterator end, T&ref) {
    // Calcula o tamanho do intervalo do array
    const size_t input_size = std::distance(start, end);
    // Calcula o número de threads permitidas com base no tamanho do bloco
    const size_t allowed_threads_by_elements = (input_size) / MIN_BLOCK_SIZE;
    // Obtém o número máximo de threads suportadas pelo hardware
    const size_t allowed_threads_by_hardware = std::thread::hardware_concurrency();
    // Escolhe o número de threads a serem usadas (o minimo entre os dois por causa do hardware)
    size_t num_threads = std::max<size_t>(1, std::min(allowed_threads_by_elements, allowed_threads_by_hardware));

    // Calcula o tamanho do bloco para cada thread
    size_t block_size = (input_size + num_threads - 1) / num_threads;

    // Armazena o resultado parcial de cada thread
    std::vector<T> results(num_threads);
    // Armazena as threads
    std::vector<std::thread> threads(num_threads - 1);

    // Inicializa o iterador 'last' com o início do intervalo
    iterator last = start;

    for (int i = 0; i < num_threads - 1; ++i) {
        iterator thread_start = start;

        // Avança 'last' para o final do bloco
        std::advance(last, block_size);
        last = thread_start;
        // Cria uma thread para chamar a função 'accumulate'
        threads[i] = std::thread(accumulate<iterator, T>, thread_start, last, std::ref(static_cast<T&>(results[i])));
        // Atualiza 'start' para o próximo bloco
        start = last;
    }

    // Último bloco processado na thread principal
    results[num_threads - 1] = std::accumulate(start, end, 0);
    // Aguarda a conclusão de todas as threads
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    // Soma final dos resultados parciais
    return std::accumulate(results.begin(), results.end(), ref);
}


/**
 * \brief A função abaixo realiza uma serie de acumulação utilizando a função std::accumulate da lib <numeric>
 */
void sequetial_accumulate_test(std::vector<int>& v) {


    // A primeira utilização da função accumulate faz a soma dos numeros do vetor v
    const int sum = std::accumulate(v.begin(), v.end(), 0);

    // A segunda utilização da função faz o produto dos numeros do vetror v
    // const int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<>());

    // A terceira utilização da função é utilizada em um função lambda que tem como o objetivo concatenar uma string
    auto dash_fold = [](std::string a, int b) {
        return std::move(a) + "-" + std::to_string(b);
    };

    std::string s = std::accumulate(std::next(v.begin()), v.end(), std::to_string(v[0]), dash_fold);

    std::cout << "sum - " << sum << "\n";

    // std::cout << "product - " << product << "\n";
    //
    // std::cout << "dash function - " << s << "\n";
}


int main(int argc, char* argv[]) {

    constexpr int size = 8000;
    const auto my_array = new int[size];
    int ref = 0;
    std::vector<int> my_vector(size);

    srand(0);

    for (size_t i = 0; i < size; i++) {
        my_array[i] = rand() % 10;
        my_vector[i] = rand() % 10;
    }


    sequetial_accumulate_test(my_vector);

    const int rer_val = parallel_accumulate<int *, int>(my_array, my_array + size, ref);
    printf("Accumulated value : %d \n", rer_val);
}
