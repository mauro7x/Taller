// includes de C
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdint.h>

/* Escriba una rutina que procese un archivo binario indicado por parámetro sobre sí mismo
sumarizando los listados de números que posee almacenado. La sumarización consiste en
recorrer los valores enteros de 32 bits con signo grabados en formato big-endian y acumular sus
valores hasta encontrar el valor '0xFFFFFFFF' que se considera un separador entre
listados. Todos los valores enteros detectados son reemplazados por su sumatoria (en el mismo
formato) manteniendo luego el elemento separador. Considere archivos bien formados. */

void armar_archivo(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        exit(1);
    }
    int32_t val;
    val = (int32_t) htonl(12);
    fwrite(&val, sizeof(val), 1, fp);
    val = (int32_t) htonl(7);
    fwrite(&val, sizeof(val), 1, fp);
    val = (int32_t) htonl(2);
    fwrite(&val, sizeof(val), 1, fp);
    val = (int32_t) htonl(0xFFFFFFFF);
    fwrite(&val, sizeof(val), 1, fp);
    val = (int32_t) htonl(-3);
    fwrite(&val, sizeof(val), 1, fp);
    val = (int32_t) htonl(-4);
    fwrite(&val, sizeof(val), 1, fp);
    val = (int32_t) htonl(7);
    fwrite(&val, sizeof(val), 1, fp);
    val = (int32_t) htonl(0xFFFFFFFF);
    fwrite(&val, sizeof(val), 1, fp);
    
    fclose(fp);
}

bool read_int32_be(int32_t* val, FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    if (!fread(val, sizeof(int32_t), 1, fp)) {
        return false;
    }

    *offset = ftell(fp);
    *val = (int32_t) ntohl(*val);
    return true;
}

bool write_int32_be(const int32_t* val, FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    int32_t aux = (int32_t) htonl(*val);
    if (!fwrite(&aux, sizeof(int32_t), 1, fp)) {
        return false;
    }

    *offset = ftell(fp);
    return true;
}


int main(int argc, char *argv[]) {
    const char* filename = "ej8.bin";
    armar_archivo(filename);

    FILE* fp = fopen(filename, "rt+");
    if (!fp) {
        return 1;
    }

    size_t final_size = 0;
    long read_seek = 0;
    long write_seek = 0;
    int32_t sum = 0;
    int32_t val = 0;
    int32_t delimiter = 0xFFFFFFFF; 

    while (read_int32_be(&val, fp, &read_seek)) {
        if (val == delimiter) {
            write_int32_be(&sum, fp, &write_seek);
            write_int32_be(&delimiter, fp, &write_seek);
            final_size += sizeof(sum) + sizeof(delimiter);
            sum = 0;
        } else {
            sum += val;
        }
    }

    ftruncate(fileno(fp), final_size);
    fclose(fp);
    return 0;
}