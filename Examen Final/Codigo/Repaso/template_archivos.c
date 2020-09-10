// includes de C
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* Consigna */

void armar_archivo(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        exit(1);
    }

    // Armar archivo.

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
    const char* filename = "nombre";
    armar_archivo(filename);

    FILE* fp = fopen(filename, "rt+");
    if (!fp) {
        return 1;
    }

    // Ejercicio

    // ...

    // Fin del ejercicio

    fclose(fp);
    return 0;
}