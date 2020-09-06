// includes
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERROR(msg, ...)                \
    fprintf(stderr, msg, __VA_ARGS__); \
    exit(1)

/* Escriba un programa C que tome 2 cadenas por línea de comandos: A y B; e
imprima la cadena A después de haber duplicado todas las ocurrencias de B.

Ej.: reemp.exe "Este es el final" final -----> Este es el final final */

char* duplicar_ocurrencia(const char* A, const char* B);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        ERROR("usage: %s <A> <B>\n", argv[0]);
    }

    const char* A = argv[1];
    const char* B = argv[2];

    char* ret = duplicar_ocurrencia(A, B);
    fprintf(stderr, "A = [%s]\nB = [%s]\nResultado = [%s]\n", A, B, ret);
    free(ret);

    return 0;
}

char* duplicar_ocurrencia(const char* A, const char* B) {
    size_t A_len = strlen(A);
    size_t B_len = strlen(B);

    size_t ocurrencias = 0;

    for (size_t i = 0; i < A_len; i++) {
        if (strncmp(&A[i], B, B_len) == 0) {
            ocurrencias++;
        }
    }

    size_t ret_len = A_len + (ocurrencias * B_len);
    char* ret = (char*)malloc(ret_len + 1);

    size_t ret_i = 0;
    for (size_t i = 0; i < A_len; i++) {
        if (strncmp(&A[i], B, B_len) == 0) {
            strncpy(&ret[ret_i], B, B_len);
            ret_i += B_len;
        }

        ret[ret_i] = A[i];
        ret_i++;
    }

    ret[ret_len] = '\0';
    return ret;
}