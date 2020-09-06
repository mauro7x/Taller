// includes
#include <stdio.h>

#include <iostream>
#include <list>

template <class T>
std::list<T> DobleSegunda(const std::list<T>& a, const std::list<T>& b) {
    std::list<T> c;

    bool duplicar = false;
    for (auto it_a = a.begin(); it_a != a.end(); it_a++) {
        c.push_back(*it_a);
        duplicar = false;

        for (auto it_b = b.begin(); it_b != b.end(); it_b++) {
            if (*it_a == *it_b) {
                duplicar = true;
                break;
            }
        }

        if (duplicar) {
            c.push_back(*it_a);
        }
    }

    return c;
}

template <class T>
void imprimir_lista(const std::list<T>& list) {
    for (auto it = list.begin(); it != list.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    std::list<int> a = {1, 2, 3};
    std::list<int> b = {2};
    std::list<int> c;

    c = DobleSegunda(a, b);

    fprintf(stderr, "aca!\n");

    imprimir_lista(a);
    imprimir_lista(b);
    imprimir_lista(c);

    return 0;
}

// definiciones
