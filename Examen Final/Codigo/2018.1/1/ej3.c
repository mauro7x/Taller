#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Escribir un programa que procese un archivo binario de enteros
sin signo sobre si mismo. El procesamiento consiste en leer pares
de enteros de 1 byte cada uno y reemplazarlos por 3 enteros
(el archivo se agranda): su suma, su resta y el OR logico entre ambos. */

void armar_archivo(const char* filename) {
    FILE* fp = fopen(filename, "wb");
    // TODO chequear si se abrio

    fputc(1, fp);
    fputc(2, fp);

    fputc(3, fp);
    fputc(6, fp);

    fputc(8, fp);
    fputc(3, fp);

    fputc(10, fp);
    fputc(11, fp);

    fclose(fp);
}

size_t read_int8_backwards(FILE* fp, long* offset, int8_t* val) {
    if (--(*offset) < 0) {
        return 0;
    }

    fseek(fp, *offset, SEEK_SET);
    return fread(val, sizeof(int8_t), 1, fp);
}

size_t write_int8_backwards(FILE* fp, long* offset, int8_t val) {
    if (--(*offset) < 0) {
        return 0;
    }

    fseek(fp, *offset, SEEK_SET);
    return fwrite(&val, sizeof(int8_t), 1, fp);
}

int main(int argc, char* argv[]) {
    const char* filename = "int8pairs.bin";
    armar_archivo(filename);

    FILE* fp = fopen(filename, "rb+");
    // TODO ver si se abrió bien

    // Sabemos que el archivo se compone por pares de bytes, y que por cada
    // par de bytes, se agrega un tercer byte.
    // Calculamos el tamaño final del archivo con esta información.

    size_t final_bytes, original_bytes;
    long read_seek, write_seek;

    fseek(fp, 0, SEEK_END);
    original_bytes = ftell(fp);
    final_bytes = original_bytes + (original_bytes/2);
    ftruncate(fileno(fp), final_bytes);

    read_seek = original_bytes;
    write_seek = final_bytes;

    int8_t val1, val2, aux;
    bool eof = false;
    while (!eof) {
        eof = !read_int8_backwards(fp, &read_seek, &val2);
        eof |= !read_int8_backwards(fp, &read_seek, &val1);

        if (eof) {
            break;
        }

        write_int8_backwards(fp, &write_seek, val1 | val2);
        write_int8_backwards(fp, &write_seek, val1 - val2);
        write_int8_backwards(fp, &write_seek, val1 + val2);
    }

    fclose(fp);
    return 0;
}
