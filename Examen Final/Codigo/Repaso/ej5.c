// includes de C
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* Escribir un programa C que reciba por argumento el nombre de un archivo, y lo procese
sobre sí mismo (sin crear archivos intermedios). El procesamiento consiste en eliminar toda
secuncia de caracteres consecutivos repetidos, dejando en su lugar un solo carácter de dicha
secuencia. ej.: la cadena "abcddeeefgggghee" debe ser reemplazada por "abcdefghe" */

#define BUF_LEN 1024

void armar_archivo(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        exit(1);
    }

    fputs("abcddeeefgggghee", fp);

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
    const char* filename = "ej5.txt";
    armar_archivo(filename);

    FILE* fp = fopen(filename, "rt+");
    if (!fp) {
        return 1;
    }

    size_t total_bytes = 0;
    long read_seek = 0;
    long write_seek = 0;
    char buffer[BUF_LEN];
    size_t buffer_len;
    char last_c = 0;

    while(read_line(buffer, BUF_LEN, fp, &read_seek)) {
        buffer_len = strlen(buffer);
        for (size_t i = 0; i < buffer_len; i++) {
            if (buffer[i] != last_c) {
                write_c(buffer[i], fp, &write_seek);
                last_c = buffer[i];
                total_bytes++;
            }
        }
    }    

    ftruncate(fileno(fp), total_bytes);
    fclose(fp);
    return 0;
}