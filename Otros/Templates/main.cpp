#include <iostream>

#include "Array.h"
#include "Foo.h"

int main() {

    Array ints;
    ints.set(0, 50);
    std::cout << ints.get(0) << std::endl;
    
    ints.saludar(100);
    ints.saludar('A');
    

    /*
    Array<int> ints;
    ints.set(0, 50);
    std::cout << ints.get(0) << std::endl;
    ints.saludar(200);
    ints.saludar('A');
    ints.saludar<char>(120);
    */



    //foo(100);
    //foo('L');

    return 0;
}