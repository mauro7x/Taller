// includes
#include <stdio.h>
#include <iostream>
#include <list>

// declaraciones
void imprimir_lista(std::list<int> lista);
std::list<int> DobleSiNo(const std::list<int> a, const std::list<int> b);

int main(int argc, char* argv[]) {
    
    std::list<int> a = {1, 2, 3, 4, 5, 6, 7};
    std::list<int> b = {1, 3, 5, 7};
    std::list<int> c = DobleSiNo(a, b);

    imprimir_lista(a);
    imprimir_lista(b);
    imprimir_lista(c);

    return 0;
}

// definiciones
void imprimir_lista(std::list<int> lista) {
    for (auto it = lista.begin(); it != lista.end(); it++) {
        fprintf(stdout, "%d ", *it);
    }

    fprintf(stdout, "\n");
}

std::list<int> DobleSiNo(const std::list<int> a, const std::list<int> b) {
    std::list<int> c = a;

    bool esta = false;

    for (auto it = c.begin(); it != c.end(); it++;) {
        esta = false;

        for (auto it_b = b.begin(); it_b != b.end(); it_b++) {
            if (*it == *it_b) {
                esta = true;
                break;
            }
        }

        if (!esta) {
            it = ++(c.insert(it, *it));
        }
    }

    return c;
}
