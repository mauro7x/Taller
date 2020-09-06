// includes
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Escribir un programa ISO C que reciba por argumento el nombre de un archivo
 * de texto y lo procese sobre sí mismo (sin crear archivos intermedios ni
 * subiendo todo su contenido a memoria). El procesamiento consiste en eliminar
 * las líneas de 1 sola palabra.*/

int read_c(FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    int out = fgetc(fp);
    *offset = ftell(fp);
    return out;
}

int write_c(int c, FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    int out = fputc(c, fp);
    *offset = ftell(fp);
    return out;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];

    // Ejercicio de truncamiento de archivo de texto.
    FILE* fp = fopen(filename, "rt+");
    if (!fp) {
        fprintf(stderr, "error opening file\n");
        return 1;
    }

    size_t final_size = 0;
    long read_seek = 0;
    long write_seek = 0;
    size_t words = 0;
    size_t line_len = 0;
    int c, previous_c;

    while ((c = read_c(fp, &read_seek)) != EOF) {
        final_size++;

        if (c == '\n') {
            if (previous_c != ' ' && previous_c != '\n') {
                words++;
            }

            // TODO analizar si pisamos la linea o no
            if (words > 1) {
                write_c(c, fp, &write_seek);
            } else {
                write_seek -= line_len;
                final_size -= line_len + 1;
            }

            // reset
            words = 0;
            line_len = 0;
        } else {
            if ((c == ' ') && (previous_c != '\n') && (previous_c != ' ')) {
                words++;
            }

            line_len++;
            write_c(c, fp, &write_seek);
        }

        previous_c = c;
    }

    // TODO analizar ultima linea
    if (previous_c != ' ' && previous_c != '\n') {
        words++;
    }

    // TODO analizar si pisamos la linea o no
    if (words <= 1) {
        final_size -= line_len;
    }

    ftruncate(fileno(fp), final_size);
    fclose(fp);
    return 0;
}
