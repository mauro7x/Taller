// includes
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Escribir un programa ISO C que procese el archivo "nros_2bytes_bigendian.dat"
 * sobre sí mismo, eliminando los número múltiplos de 7. */

void armar_archivo(const char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "no se pudo crear el archivo\n");
        exit(1);
    }

    uint16_t val;
    val = htons(1);
    fwrite(&val, sizeof(val), 1, fp);

    val = htons(14);
    fwrite(&val, sizeof(val), 1, fp);

    val = htons(5);
    fwrite(&val, sizeof(val), 1, fp);

    val = htons(7);
    fwrite(&val, sizeof(val), 1, fp);

    val = htons(8);
    fwrite(&val, sizeof(val), 1, fp);

    fclose(fp);
}

int read_2bytes_bigendian(uint16_t* val, FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    int out = fread(val, sizeof(uint16_t), 1, fp);
    if (out) {
        *val = htons(*val);
    }
    *offset = ftell(fp);
    return out;
}

int write_2bytes_bigendian(uint16_t* val, FILE* fp, long* offset) {
    *val = htons(*val);
    fseek(fp, *offset, SEEK_SET);
    int out = fwrite(val, sizeof(uint16_t), 1, fp);
    *offset = ftell(fp);
    return out;
}

int main(int argc, char* argv[]) {
    const char* filename = "nros_2bytes_bigendian.dat";
    armar_archivo(filename);

    FILE* fp = fopen(filename, "rb+");
    if (!fp) {
        fprintf(stderr, "no se pudo abrir el archivo\n");
        exit(1);
    }

    size_t final_bytes = 0;
    long read_seek = 0;
    long write_seek = 0;
    uint16_t val = 0;

    while (read_2bytes_bigendian(&val, fp, &read_seek)) {
        if (!(val % 7)) {
            continue;
        }

        final_bytes += sizeof(uint16_t);
        write_2bytes_bigendian(&val, fp, &write_seek);
    }

    ftruncate(fileno(fp), final_bytes);
    fclose(fp);
    return 0;
}
