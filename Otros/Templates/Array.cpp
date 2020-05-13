#include "Array.h"

#include <iostream>

Array::Array() {}

Array::~Array() {}

void Array::set(int p, int v) {
    data[p] = v;
}

int Array::get(int p) {
    return data[p];
}
