// includes
#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <vector>
#include <algorithm>
#include <cstdint>

int main(int argc, char* argv[]) {
    std::mutex m;
    m.lock();
    std::thread t1([](std::mutex& m){
        m.lock(); // se bloquea esperando que el mutex m se libere
        m.unlock();
    }, std::ref(m));

    t1.join(); // se bloquea esperando a que t1 termine
    m.unlock();

    return 0;
}
