#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
Escriba un programa C que reciba por parámetro el nombre de un archivo de
números binarios de 16 bits y lo procese sobre sí mismo. El procesamiento
consiste en repetir los números que sean "múltiplos de 5 + 1" (6, 11, 16...) (El
archivo se agranda)
*/

#define ERROR(msg)                                                    \
    fprintf(stderr, "error in %s:%d: %s\n", __FILE__, __LINE__, msg); \
    exit(1)

#define NEED_TO_EXPAND(val) ((((val) % 5) == 1) && (val != 1))

// función para armar el archivo según lo pedido por el enunciado
void armar_archivo();

void leer_reversa(void* ptr, size_t size, size_t nmemb, FILE* fp, long* offset);
void escribir_reversa(const void* ptr, size_t size, size_t nmemb, FILE* fp,
                      long* offset);

int main(int argc, char* argv[]) {
    const char* filename = "num_u16.bin";
    armar_archivo(filename);

    FILE* fp = fopen(filename, "rb+");
    if (!fp) {
        ERROR("no se pudo abrir el archivo");
    }

    // ejercicio

    // vamos a recorrer todo el archivo primero, para agregar los bytes al final
    // que hagan falta. después, lo expandimos desde atrás hacia adelante.
    size_t original_bytes = 0;
    size_t extra_bytes = 0;

    // asumo que son sin signo
    uint16_t val;

    // asumimos que el archivo está bien formado
    while (fread(&val, sizeof(val), 1, fp)) {
        fprintf(stderr, "lei valor de 2 bytes: %u\n", val);
        original_bytes += 2;

        if (NEED_TO_EXPAND(val)) {
            extra_bytes += 2;
        }
    }

    long seek_read = ftell(fp);

    // dejamos lugar para los bytes extra
    ftruncate(fileno(fp), original_bytes + extra_bytes);

    fseek(fp, 0, SEEK_END);
    long seek_write = ftell(fp);

    // expandimos
    size_t total_nums = original_bytes / sizeof(uint16_t);
    for (size_t num = 0; num < total_nums; num++) {
        leer_reversa(&val, sizeof(val), 1, fp, &seek_read);
        fprintf(
            stderr,
            "[expandiendo] lei val = %u, seek_read = %ld, seek_write = %ld\n",
            val, seek_read, seek_write);

        escribir_reversa(&val, sizeof(val), 1, fp, &seek_write);
        if (NEED_TO_EXPAND(val)) {
            escribir_reversa(&val, sizeof(val), 1, fp, &seek_write);
        }
    }

    fclose(fp);
    return 0;
}

void armar_archivo(const char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        ERROR("no se pudo abrir el archivo");
    }

    uint16_t value;
    value = 1;
    fwrite(&value, sizeof(value), 1, fp);
    value = 2;
    fwrite(&value, sizeof(value), 1, fp);
    value = 4;
    fwrite(&value, sizeof(value), 1, fp);
    value = 5;
    fwrite(&value, sizeof(value), 1, fp);
    value = 6;
    fwrite(&value, sizeof(value), 1, fp);
    value = 10;
    fwrite(&value, sizeof(value), 1, fp);
    value = 11;
    fwrite(&value, sizeof(value), 1, fp);
    value = 12;
    fwrite(&value, sizeof(value), 1, fp);
    value = 30;
    fwrite(&value, sizeof(value), 1, fp);
    value = 31;
    fwrite(&value, sizeof(value), 1, fp);
    value = 32;
    fwrite(&value, sizeof(value), 1, fp);

    fclose(fp);
}

void leer_reversa(void* ptr, size_t size, size_t nmemb, FILE* fp,
                  long* offset) {
    *offset -= size;
    fseek(fp, *offset, SEEK_SET);
    fread(ptr, size, nmemb, fp);
}

void escribir_reversa(const void* ptr, size_t size, size_t nmemb, FILE* fp,
                      long* offset) {
    *offset -= size;
    fseek(fp, *offset, SEEK_SET);
    fwrite(ptr, size, nmemb, fp);
}