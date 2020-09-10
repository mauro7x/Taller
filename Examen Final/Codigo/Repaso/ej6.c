// includes de C
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* Escribir un programa C que reciba por argumento el nombre de un archivo de texto y lo
procese sobre sí mismo (sin crear archivos intermedios). El procesamiento consiste en
reemplazar todas las ocurrencias de '1', '2' y '3' (con un separador antes y uno después) por
'uno', 'dos' y 'tres', respectivamente. */

#define MAX_LINE_LEN 1024

void armar_archivo(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        exit(1);
    }

    fputs("Hola como estas? 1 2 3 probandoooo acá no se debería reemplazar: 123.txt.\nPero aca: 1 sí debería 2 reemplazarse.", fp);

    fclose(fp);
}

bool read_s(char* buffer, size_t max_size, FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    char* aux = fgets(buffer, max_size, fp);
    *offset = ftell(fp);
    return (aux != NULL);
}

bool write_s(const char* buffer, FILE* fp, long* offset) {
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

int read_c_backwards(FILE* fp, long* offset) {
    (*offset)--;
    if (*offset < 0) {
        return EOF;
    }
    fseek(fp, *offset, SEEK_SET);
    return fgetc(fp);
}

int write_c_backwards(int c, FILE* fp, long* offset) {
    (*offset)--;
    if (*offset < 0) {
        return EOF;
    }
    fseek(fp, *offset, SEEK_SET);
    return fputc(c, fp);
}

int main(int argc, char *argv[]) {
    const char* filename = "ej6.txt";
    armar_archivo(filename);

    FILE* fp = fopen(filename, "rt+");
    if (!fp) {
        return 1;
    }

    // Ejercicio

    char line[MAX_LINE_LEN];
    size_t line_len;
    size_t final_size = 0;
    long read_seek = 0;
    long write_seek = 0;
    size_t offset;

    char to_comp_1[] = " 1 ";
    char to_repl_1[] = " uno ";
    size_t to_comp_1_len = strlen(to_comp_1);
    size_t to_repl_1_len = strlen(to_repl_1);

    char to_comp_2[] = " 2 ";
    char to_repl_2[] = " dos ";
    size_t to_comp_2_len = strlen(to_comp_2);
    size_t to_repl_2_len = strlen(to_repl_2);

    char to_comp_3[] = " 3 ";
    char to_repl_3[] = " tres ";
    size_t to_comp_3_len = strlen(to_comp_3);
    size_t to_repl_3_len = strlen(to_repl_3);

    // Calculamos longitud final

    while (read_s(line, MAX_LINE_LEN, fp, &read_seek)) {
        line_len = strlen(line);
        for (size_t i = 0; i < line_len;) {
            if (strncmp(&line[i], to_comp_1, to_comp_1_len) == 0) {
                final_size += to_repl_1_len;
                i += to_comp_1_len;
            } else if (strncmp(&line[i], to_comp_2, to_comp_2_len) == 0) {
                final_size += to_repl_2_len;
                i += to_comp_2_len;
            } else if (strncmp(&line[i], to_comp_3, to_comp_3_len) == 0) {
                final_size += to_repl_3_len;
                i += to_comp_3_len;
            } else {
                final_size++;
                i++;
            }
        }
    }

    ftruncate(fileno(fp), final_size);
    offset = final_size - read_seek;
    write_seek = final_size;

    // Desplazamos el archivo
    int c;
    while ((c = read_c_backwards(fp, &read_seek)) != EOF) {
        write_c_backwards(c, fp, &write_seek);
    }

    // Expandimos
    read_seek = offset;
    write_seek = 0;

    while (read_s(line, MAX_LINE_LEN, fp, &read_seek)) {
        line_len = strlen(line);
        for (size_t i = 0; i < line_len;) {
            if (strncmp(&line[i], to_comp_1, to_comp_1_len) == 0) {
                write_s(to_repl_1, fp, &write_seek);
                i += to_comp_1_len;
            } else if (strncmp(&line[i], to_comp_2, to_comp_2_len) == 0) {
                write_s(to_repl_2, fp, &write_seek);
                i += to_comp_2_len;
            } else if (strncmp(&line[i], to_comp_3, to_comp_3_len) == 0) {
                write_s(to_repl_3, fp, &write_seek);
                i += to_comp_3_len;
            } else {
                write_c(line[i], fp, &write_seek);
                i++;
            }
        }
    }

    // Fin del ejercicio

    fclose(fp);
    return 0;
}