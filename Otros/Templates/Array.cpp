#include "Array.h"

Array::Array() {}

Array::~Array() {}

void Array::set(int p, int v) {
    data[p] = v;
}

int Array::get(int p) {
    return data[p];
}

template<>
void Array::saludar<char>(char c) {
    std::cout << "Para chars: " << c << "\n";
}
