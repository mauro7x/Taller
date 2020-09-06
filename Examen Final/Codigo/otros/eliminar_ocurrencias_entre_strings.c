#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define error(msg)                       \
    fprintf(stderr, "error: %s\n", msg); \
    exit(1);

// elimina las ocurrencias de b en a
void eliminar_ocurrencias(char* a, const char* b);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        error("bad arguments");
    }

    char* A = argv[1];
    char* B = argv[2];

    fprintf(stderr, "A = [%s]\nB = [%s]\n", A, B);

    eliminar_ocurrencias(A, B);

    fprintf(stderr, "RESULTADO = [%s]\n", A);

    return 0;
}

void eliminar_ocurrencias(char* a, const char* b) {
    size_t a_len = strlen(a);
    size_t b_len = strlen(b);

    // [h][o][l][a][ ][c][o][m][o][ ][e][s][t][a][s][\0]
    //  0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15(len)

    for (size_t i = 0; i < a_len; i++) {
        if (!strncmp(&a[i], b, b_len)) {
            strncpy(&a[i], &a[i + b_len], a_len - (i + b_len));
            a_len -= b_len;
            a[a_len] = '\0';
        }
    }
}