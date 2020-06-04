#include <iostream>

#include "Exception.h"
#include "Particular.h"

int main(int argc, char* argv[]) {
    try {
        throw Exception("Error %s, errno: ", "sos puto");

    } catch (const Exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}