#include <iomanip>
#include <iostream>

#define LEVEL 10

int main() {
    int i, n, h;
    h = LEVEL - 1;
    std::cout << std::setw(h + 2);
    h = h - 1;
    for (i = -1; i < LEVEL; i++) {
        for (n = 1; n < (i + 2); n++) {
            std::cout << "* ";
        }
        std::cout << std::setw(h + 3) << std::endl;
        h--;
    }
    std::cout << "\n";
    return 0;
}