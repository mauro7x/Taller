// includes
#include <stdio.h>

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

/* Escriba un programa que imprima por salida estándar los números entre 1 y
 * 100, en orden ascendente. Se pide que los números sean contabilizados por una
 * variable global única y que los pares sean escritos por un hilo mientras que
 * los impares sean escritos por otro. Contemple la correcta sincronización
 * entre hilos y la liberación de los recursos utilizados. */

int num = 1;

class Impresor {
   private:
    std::mutex m;
    std::condition_variable escribir_par, escribir_impar;

   public:
    Impresor() {}
    ~Impresor() {}

    void imprimir_par() {
        std::unique_lock<std::mutex> l(m);
        while ((num % 2)) {
            // es impar
            escribir_par.wait(l);
        }

        std::cout << num++ << std::endl;
        escribir_impar.notify_one();
    }

    void imprimir_impar() {
        std::unique_lock<std::mutex> l(m);
        while (!(num % 2)) {
            // es par
            escribir_impar.wait(l);
        }

        std::cout << num++ << std::endl;
        escribir_par.notify_one();
    }
};

int main(int argc, char* argv[]) {
    Impresor impresor;

    std::thread t1(
        [](Impresor& impresor) {
            for (int i = 0; i < 50; i++) {
                impresor.imprimir_par();
            }
        },
        std::ref(impresor));

    std::thread t2(
        [](Impresor& impresor) {
            for (int i = 0; i < 50; i++) {
                impresor.imprimir_impar();
            }
        },
        std::ref(impresor));

    t1.join();
    t2.join();

    return 0;
}

// definiciones
