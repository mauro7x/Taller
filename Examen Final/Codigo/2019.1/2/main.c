// includes
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Escribir un programa C que procese el archivo "numeros.txt" sobre sí mismo
 * (sin crear archivos intermedios y sin subir el archivo a memoria). El
 * procesamiento consiste en leer grupos de 4 caracteres hexadecimales y
 * reemplazarlos por los correspondientes dígitos decimales (que representen el
 * mismo número leído pero en decimal). */

void armar_archivo(const char* filename);

bool read_string(char* buffer, size_t n, FILE* fp, long* offset);
int write_string(const char* buffer, size_t n, FILE* fp, long* offset);

bool read_string_reversa(char* buffer, size_t n, FILE* fp, long* offset);
int write_string_reversa(const char* buffer, size_t n, FILE* fp, long* offset);

int main(int argc, char* argv[]) {
    const char* filename = "numeros.txt";
    armar_archivo(filename);

    FILE* fp = fopen(filename, "rt+");

    char buffer[5];
    char buffer_dec[6];
    size_t final_bytes = 0;
    long read_seek = 0;
    long write_seek = 0;
    long val;

    while (read_string(buffer, sizeof(buffer), fp, &read_seek)) {
        fprintf(stderr, "lei: [%s]\n", buffer);
        final_bytes += 5;
    }

    ftruncate(fileno(fp), final_bytes);

    fseek(fp, 0, SEEK_END);
    write_seek = ftell(fp);

    while (read_string_reversa(buffer, sizeof(buffer), fp, &read_seek)) {
        val = strtol(buffer, NULL, 16);

        snprintf(buffer_dec, sizeof(buffer_dec), "%05ld", val);

        write_string_reversa(buffer_dec, sizeof(buffer_dec) - 1, fp,
                             &write_seek);
    }

    fclose(fp);
    return 0;
}

void armar_archivo(const char* filename) {
    FILE* fp = fopen(filename, "wt");

    char buffer[5];
    snprintf(buffer, 5, "%04x", 10);
    fputs(buffer, fp);

    snprintf(buffer, 5, "%04x", 7);
    fputs(buffer, fp);

    snprintf(buffer, 5, "%04x", 2);
    fputs(buffer, fp);

    snprintf(buffer, 5, "%04x", 50);
    fputs(buffer, fp);

    snprintf(buffer, 5, "%04x", 25);
    fputs(buffer, fp);

    fclose(fp);
}

bool read_string(char* buffer, size_t n, FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    char* aux = fgets(buffer, n, fp);
    *offset = ftell(fp);
    return (aux != NULL);
}

int write_string(const char* buffer, size_t n, FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    int out = fputs(buffer, fp);
    *offset = ftell(fp);
    return out;
}

bool read_string_reversa(char* buffer, size_t n, FILE* fp, long* offset) {
    if (*offset == 0) {
        return false;
    }

    *offset -= (n - 1);
    fseek(fp, *offset, SEEK_SET);
    char* aux = fgets(buffer, n, fp);
    return (aux != NULL);
}
int write_string_reversa(const char* buffer, size_t n, FILE* fp, long* offset) {
    if (*offset == 0) {
        return EOF;
    }

    *offset -= n;
    fseek(fp, *offset, SEEK_SET);
    int out = fputs(buffer, fp);
    return out;
}