#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

/* Implemente la funcion ``void String_a_Int(char *bin, int *ent)`` que
* interprete la cadena bin (de 32 1s/0s) y guarde el valor correspondiente
* en el entero indicado por ent. */

void String_a_Int(const char *bin, unsigned int *ent) {
    // asumo que tiene 32 de largo
    // asumo unsigned int por facilidad
    size_t exponent = 31;
    unsigned int res = 0;

    for (size_t i = 0; i < 32; i++) {
        if (bin[i] == '1') {
            res += pow(2, exponent);
        }

        exponent--;
    }

    *ent = res;
}

int main(int argc, char* argv[]) {
    unsigned int a;
    const char* bin = "00000000000000000000000000100100";
    String_a_Int(bin, &a);

    printf("bin: [%s], ent: %u\n", bin, a);

    return 0;
}
