// includes
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Escriba una función ISO C que permita procesar un archivo texto que contenga
 * frases (1 por línea) sobre sí mismo, sin generar archivos intermedios ni
 * cargar el archivo completo a memoria. El procesamiento consiste en eliminar
 * las palabras de más de 3 letras de cada línea. */

#define MAX_WORD_LEN 3

int leer_c(FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    int out = fgetc(fp);
    *offset = ftell(fp);
    return out;
}

int escribir_c(int c, FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    int out = fputc(c, fp);
    *offset = ftell(fp);
    return out;
}

int main(int argc, char* argv[]) {
    const char* filename = "dat.txt";
    FILE* fp = fopen(filename, "rt+");
    if (!fp) {
        return 1;
    }

    size_t final_bytes = 0;
    size_t word_len = 0;
    long seek_lectura = 0;
    long seek_escritura = 0;
    char c;

    while ((c = leer_c(fp, &seek_lectura)) != EOF) {
        if (c == ' ' || c == '\n') {
            if (word_len > MAX_WORD_LEN) {
                // eliminar palabra
                seek_escritura -= word_len;
                final_bytes -= word_len;

                if (c == ' ') {
                    word_len = 0;
                    continue;
                }
            }

            word_len = 0;
        } else {
            word_len++;
        }

        final_bytes++;
        escribir_c(c, fp, &seek_escritura);
    }

    // ultima palabra
    if (word_len > MAX_WORD_LEN) {
        seek_escritura -= word_len;
        final_bytes -= word_len;
    }

    ftruncate(fileno(fp), final_bytes);
    fclose(fp);
    return 0;
}
