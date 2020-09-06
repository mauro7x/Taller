// includes
#include <stdio.h>

#include <iostream>

class Numero {
   public:
    static int a;
    Numero() {}
    ~Numero() {}
};

// int Numero::a = 0;

int main(int argc, char* argv[]) {
    Numero numero;
    std::cout << numero.a << std::endl;
    return 0;
}

// definiciones
