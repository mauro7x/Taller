// includes
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Escriba una función ISO C llamada Replicar que reciba 1 cadena (S), dos
índices (I1 e I2) y una cantidad (Q). La función debe retornar una copia de S
salvo los caracteres que seencuentran entre los índices I1 e I2 que serán
duplicados Q veces. Ej. `replicar("Hola", 1, 2, 3)` retorna "Hololola". */

char* replicar(const char* S, size_t I1, size_t I2, size_t Q);

int main(int argc, char* argv[]) {
    // codigo
    const char* S = argv[1];
    size_t I1 = strtoul(argv[2], NULL, 10);
    size_t I2 = strtoul(argv[3], NULL, 10);
    size_t Q = strtoul(argv[4], NULL, 10);
    char* ret = replicar(S, I1, I2, Q);

    fprintf(stdout, "Resultado = [%s]\n", ret);
    free(ret);

    return 0;
}

char* replicar(const char* S, size_t I1, size_t I2, size_t Q) {
    size_t original_len = strlen(S);
    if (I1 > I2 || I2 >= original_len) {
        return NULL;
    }

    // calculamos el nuevo largo
    size_t final_len = original_len + (I2 - I1 + 1) * (Q - 1);
    char* ret = (char*)malloc(final_len + 1);

    // copiar y expandir
    strncpy(ret, S, I1);
    for (size_t i = 0; i < Q; i++) {
        strncat(ret, &S[I1], (I2 - I1 + 1));
    }
    strncat(ret, &S[(I2 + 1)], (original_len - (I2 + 1)));
    return ret;
}

// definiciones
