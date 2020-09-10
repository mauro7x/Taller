// includes de C
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* Escribir un programa C que reciba por argumento el nombre de un archivo, y lo procese
sobre sí mismo (sin crear archivos intermedios). El procesamiento consiste en eliminar todos las
ocurrencias de la cadena "ABCD".
ej.: la cadena "01 23 AABCDD 45" debe ser reemplazada por "01 23 AD 45" */

#define MAX_LINE_LEN 1024

void armar_archivo(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        exit(1);
    }

    fputs("hOLA COMO ESTAS ESTE ES EL ABCDARIO: ABCDEFGHI me aburri je", fp);

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

int main(int argc, char *argv[]) {
    const char* filename = "ej7.txt";
    armar_archivo(filename);

    FILE* fp = fopen(filename, "rt+");
    if (!fp) {
        return 1;
    }

    // Ejercicio
    char to_remove[] = "ABCD";
    size_t to_remove_len = strlen(to_remove);
    size_t final_bytes = 0;
    long read_seek = 0;
    long write_seek = 0;

    char line[MAX_LINE_LEN];
    size_t line_len;

    while (read_line(line, MAX_LINE_LEN, fp, &read_seek)) {
        line_len = strlen(line);
        for (size_t i = 0; i < line_len;) {
            if (strncmp(&line[i], to_remove, to_remove_len) == 0) {
                i += to_remove_len;
            } else {
                write_c(line[i], fp, &write_seek);
                final_bytes++;
                i++;
            }
        }
    }
    
    ftruncate(fileno(fp), final_bytes);
    fclose(fp);
    return 0;
}