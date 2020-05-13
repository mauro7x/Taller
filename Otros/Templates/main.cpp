#include <iostream>

#include "Array.h"
#include "Foo.h"

int main() {
    Array<int> ints;
    ints.set(0, 50);
    std::cout << ints.get(0) << std::endl;
    ints.saludar();

    Array<bool> bools;
    bools.set(0, true);
    std::cout << bools.get(0) << std::endl;
    bools.saludar();



    //foo(100);
    //foo('L');

    return 0;
}