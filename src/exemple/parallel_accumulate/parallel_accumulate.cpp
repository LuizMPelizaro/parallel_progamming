//
// Created by siera on 25/11/2023.

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#define MIN_BLOCK_SIZE 1000

template<typename iterator, typename T>
void accumulate(iterator start, iterator end, T&ref) {
    ref = std::accumulate(start, end, 0);
}

template<typename iterator, typename T>
T parallel_accumulate(iterator start, iterator end, T&ref) {
    const int input_size = std::distance(start, end);
    const int allowed_threads_by_elements = (input_size) / MIN_BLOCK_SIZE;

    const int allowed_threads_by_hardware = std::thread::hardware_concurrency();
    int num_threads = std::min(allowed_threads_by_elements, allowed_threads_by_hardware);

    int block_size = (input_size + num_threads - 1) / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);

    iterator last = start;

    for (int i = 0; i < num_threads - 1; ++i) {
        iterator thread_start = start;
        std::advance(last, block_size);
        last = thread_start;
        threads[i] = std::thread(accumulate<iterator, T>, thread_start, last, std::ref(results[i]));
        start = last;
    }
    results[num_threads - 1] = std::accumulate(start, end, 0);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    return std::accumulate(results.begin(), results.end(), ref);

}


/**
 * \brief A função abaixo realiza uma serie de acumulação utilizando a função std::accumulate da lib <numeric>
 */
void sequetial_accumulate_test() {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // A primeira utilização da função accumulate faz a soma dos numeros do vetor v
    const int sum = std::accumulate(v.begin(), v.end(), 0);

    // A segunda utilização da função faz o produto dos numeros do vetror v
    const int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<>());

    // A terceira utilização da função é utilizada em um função lambda que tem como o objetivo concatenar uma string
    auto dash_fold = [](std::string a, int b) {
        return std::move(a) + "-" + std::to_string(b);
    };

    std::string s = std::accumulate(std::next(v.begin()), v.end(), std::to_string(v[0]), dash_fold);

    std::cout << "sum - " << sum << "\n";

    std::cout << "product - " << product << "\n";

    std::cout << "dash function - " << s << "\n";
}


int main(int argc, char* argv[]) {
    constexpr int size = 8000;
    const auto my_array = new int[size];
    int ref = 0;

    srand(0);

    for (size_t i = 0; i < size; i++) {
        my_array[i] = rand() % 10;
    }
    sequetial_accumulate_test();

    const int rer_val = parallel_accumulate<int *, int>(my_array, my_array + size, ref);
    printf("Accumulated value : %d \n", rer_val);
}
