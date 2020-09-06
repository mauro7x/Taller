// includes
#include <stdio.h>

#include <iostream>

class Fraccion {
   private:
    int numerador;
    int denominador;

   public:
    // Constructor por defecto
    Fraccion(int numerador, int denominador);

    // Constructor move
    Fraccion(Fraccion&& movible);

    // Operador asignación para movimiento
    Fraccion&& operator=(Fraccion&& movible);

    // Operador ++
    void operator++();

    // Operador -
    Fraccion operator-(const Fraccion& other) const;

    // Operador ==
    bool operator==(const Fraccion& other) const;

    // Operador >> (carga)
    friend std::istream& operator>>(std::istream& istream, Fraccion& fraccion);

    // Operador << (impresión)
    friend std::ostream& operator<<(std::ostream& ostream, Fraccion& fraccion);

    // Operador float()
    operator float() const;

    // Método de simplificación
    void simplificar();

    // Destructor
    ~Fraccion();
};

int main(int argc, char* argv[]) {
    // codigo

    return 0;
}

// definiciones
