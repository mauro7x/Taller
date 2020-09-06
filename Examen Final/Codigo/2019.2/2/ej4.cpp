// includes
#include <stdio.h>
#include <iostream>

class Sumador {
    private:
        int current_value;

    public:
        Sumador() : current_value(0) {}
        ~Sumador() {}

        void operator()(int value) {
            current_value += value;
        }

        int get_value() const {
            return current_value;
        }
};

int main(int argc, char* argv[]) {
    
    Sumador a, b;
    std::cout << "sumador a: " << a.get_value() << std::endl;
    std::cout << "sumador b: " << b.get_value() << std::endl;

    a(3);
    b(7);

    std::cout << "sumador a: " << a.get_value() << std::endl;
    std::cout << "sumador b: " << b.get_value() << std::endl;
    
    return 0;
}

// definiciones
