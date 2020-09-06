#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Escriba una función ISO C que permita procesar un archivo texto sobre sí
mismo, que contenga una palabra por línea. El procesamiento consiste en ordenar
las palabras (líneas) alfabéticamente considerando que el archivo no entra en
memoria. */

#define MAX_LINE_SIZE 1024

void armar_archivo(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "error opening file\n");
        exit(1);
    }

    fputs(
        "hola\nque\ntal\ntodo\nbien?"
        "\nsoy\nmauro\ny\nestoy\nhaciendo\nun\nejercicio\naburrido\nde\ntaller"
        "\n",
        fp);

    fclose(fp);
}

bool read_word(char *buffer, size_t n, FILE *fp, long *offset) {
    fseek(fp, *offset, SEEK_SET);
    char *word = fgets(buffer, n, fp);
    *offset = ftell(fp);
    return (word != NULL);
}

bool write_word(const char *buffer, FILE *fp, long *offset) {
    fseek(fp, *offset, SEEK_SET);
    int ret = fputs(buffer, fp);
    *offset = ftell(fp);
    return (ret != EOF);
}

int main(int argc, char *argv[]) {
    const char *filename = "lineas_desordenadas.txt";
    armar_archivo(filename);

    FILE *fp = fopen(filename, "rt+");
    if (!fp) {
        fprintf(stderr, "error opening file\n");
        exit(1);
    }

    long seek = 0;
    char line1[MAX_LINE_SIZE], line2[MAX_LINE_SIZE];
    size_t len1, len2;
    bool ordered = false;

    while (!ordered) {
        ordered = true;

        while (true) {
            if (!read_word(line1, MAX_LINE_SIZE, fp, &seek)) {
                break;
            }

            if (!read_word(line2, MAX_LINE_SIZE, fp, &seek)) {
                break;
            }

            len1 = strlen(line1);
            len2 = strlen(line2);

            if (strcmp(line1, line2) < 0) {
                // estan ordenadas
                seek -= len2;
            } else {
                // estan desordenadas
                seek -= (len1 + len2);
                write_word(line2, fp, &seek);
                write_word(line1, fp, &seek);
                seek -= len1;
                ordered = false;
            }
        }

        seek = 0;
    }

    fclose(fp);
    return 0;
}