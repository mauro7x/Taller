#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ejecutar(int (*f)(void));

int f();

int main(void) {
    ejecutar(f);
    return 0;
}

int ejecutar(int (*f)()) {
    return f();
}

int f() {
    fprintf(stderr, "hola\n");
    return 1;
}