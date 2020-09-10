// includes de C
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* Escribir un programa ISO C que procese el archivo de texto cuyo nombre es recibido como
parámetro. El procesamiento consiste en leer oraciones y suprimir aquellas que tengan
más de 3 palabras. Asuma que el archivo no puede cargarse en memoria, pero una oración
sí puede. */

#define MAX_LINE_LEN 1024

void armar_archivo(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        exit(1);
    }

    fputs("Hola como estás?\nTodo bien?\nQué\ncontás?\njajajja como estamos ultimamente eh\nbien\n", fp);

    fclose(fp);
}

bool read_line(char* buffer, size_t max_size, FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    char* aux = fgets(buffer, max_size, fp);
    *offset = ftell(fp);
    return (aux != NULL);
}

bool write_line(const char* buffer, FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    int aux = fputs(buffer, fp);
    *offset = ftell(fp);
    return (aux != EOF);
}

bool write_c(int c, FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    int aux = fputc(c, fp);
    *offset = ftell(fp);
    return (aux == c);
}

size_t word_count(const char* line, size_t size) {
    if (!size) {
        return 0; // caso borde
    }

    size_t words = 1;
    for (size_t i = 0; i < size; i++) {
        if (line[i] == ' ') {
            words++;
        }

        // TODO: agregar chequeos para no contar como dos palabras
        // dos espacios seguidos, por ejemplo.
        // asumimos que viene bien formado por ahora.
    }

    return words;
}

int main(int argc, char *argv[]) {
    const char* filename = "ej4.txt";
    armar_archivo(filename);

    FILE* fp = fopen(filename, "rt+");
    if (!fp) {
        return 1;
    }

    size_t total_bytes = 0;
    size_t line_len = 0;
    long read_seek = 0;
    long write_seek = 0;
    char line[MAX_LINE_LEN];

    while(read_line(line, MAX_LINE_LEN, fp, &read_seek)) {
        line_len = strlen(line);
        if (line[line_len - 1] == '\n') {
            line[(line_len--) - 1] = '\0';
        }

        if (word_count(line, line_len) <= 3) {
            // La palabra se escribe
            if (total_bytes) {
                write_c('\n', fp, &write_seek);
                total_bytes++;
            }

            write_line(line, fp, &write_seek);
            total_bytes += line_len;
        }
    }    

    ftruncate(fileno(fp), total_bytes);
    fclose(fp);
    return 0;
}