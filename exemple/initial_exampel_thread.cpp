#include <iostream>
#include <thread>

void foo() {
    printf("Hello foo - %d \n", std::this_thread::get_id());
}

class callable_class {
public:
    void operator()() const {
        printf("Hello from class with function call operator %d \n", std::this_thread::get_id());
    }
};


int main() {
    std::thread thread1(foo);

    callable_class obj;
    std::thread thread2(obj);

    std::thread thread3([] {
            printf("Hello from lambda - %d \n", std::this_thread::get_id());
        }
    );

    /**
     *O comando join faz com que a execução do progama inicial fique bloqueada até que a thread principla termine a sua
     * execução
     */
    thread1.join();
    thread2.join();
    thread3.join();
    printf("Hello from main - %d !", std::this_thread::get_id());
    return 0;
}
