// includes
#include <stdio.h>

#include <iostream>

// defines
class Numero {
   private:
    unsigned long value;

   public:
    // Constructores
    Numero();
    Numero(unsigned long value);
    Numero(Numero&& movible);

    // Operadores
    friend std::ostream& operator<<(std::ostream& ostream,
                                    const Numero& numero);
    unsigned long operator()() const;
    Numero&& operator=(Numero&& movible);
    operator long() const;
    void operator++(int value);
    friend std::istream& operator>>(std::istream& istream, Numero& numero) {
        istream >> numero.value;
        return istream;
    }

    // Destructores
    ~Numero();
};

// declaraciones

int main(int argc, char* argv[]) {
    // codigo

    return 0;
}

// definiciones
