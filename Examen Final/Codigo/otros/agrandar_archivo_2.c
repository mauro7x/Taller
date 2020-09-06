#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
Escribir un programa que procese un archivo binario de enteros sin signo sobre
sí mismo. El procesamiento consiste en leer pares de enteros de 1 byte cada
uno y reemplazarlos por 3 enteros (el archivo se agranda): su suma, su resta y
el OR lógico entre ambos
*/

#define ERROR(msg)                                                    \
    fprintf(stderr, "error in %s:%d: %s\n", __FILE__, __LINE__, msg); \
    exit(1)

#define NEED_TO_EXPAND(val) ((((val) % 5) == 1) && (val != 1))

// función para armar el archivo según lo pedido por el enunciado
void armar_archivo(const char* filename);

void leer_reversa(void* ptr, size_t size, size_t nmemb, FILE* fp, long* offset);
void escribir_reversa(const void* ptr, size_t size, size_t nmemb, FILE* fp,
                      long* offset);

int main(int argc, char* argv[]) {
    const char* filename = "num_u8.bin";
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
    uint8_t val1, val2, suma, resta, or_logico;

    // asumimos que el archivo está bien formado
    while (fread(&val1, sizeof(val1), 1, fp) &&
           fread(&val2, sizeof(val2), 1, fp)) {
        fprintf(stderr, "par leído: [%u, %u]\n", val1, val2);
        original_bytes += 2;
        extra_bytes += 1;
    }

    long seek_read = ftell(fp);
    fprintf(stderr, "ftell = %ld\n", ftell(fp));

    // dejamos lugar para los bytes extra
    ftruncate(fileno(fp), original_bytes + extra_bytes);

    fseek(fp, 0, SEEK_END);
    fprintf(stderr, "ftell = %ld\n", ftell(fp));
    long seek_write = ftell(fp);

    // expandimos
    size_t total_pairs = original_bytes / (2 * sizeof(uint8_t));
    for (size_t pair = 0; pair < total_pairs; pair++) {
        leer_reversa(&val2, sizeof(val2), 1, fp, &seek_read);
        leer_reversa(&val1, sizeof(val1), 1, fp, &seek_read);

        suma = val1 + val2;
        resta = val1 - val2;
        or_logico = val1 | val2;
        escribir_reversa(&or_logico, sizeof(or_logico), 1, fp, &seek_write);
        escribir_reversa(&resta, sizeof(resta), 1, fp, &seek_write);
        escribir_reversa(&suma, sizeof(suma), 1, fp, &seek_write);

        fprintf(stderr,
                "[expandiendo] par: [%u, %u]. suma = %u, resta = %u, or = %u\n",
                val1, val2, suma, resta, or_logico);
    }

    fclose(fp);
    return 0;
}

void armar_archivo(const char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        ERROR("no se pudo abrir el archivo");
    }

    uint8_t value;
    value = 3;
    fwrite(&value, sizeof(value), 1, fp);
    value = 2;
    fwrite(&value, sizeof(value), 1, fp);

    value = 10;
    fwrite(&value, sizeof(value), 1, fp);
    value = 3;
    fwrite(&value, sizeof(value), 1, fp);

    value = 21;
    fwrite(&value, sizeof(value), 1, fp);
    value = 20;
    fwrite(&value, sizeof(value), 1, fp);

    value = 50;
    fwrite(&value, sizeof(value), 1, fp);
    value = 56;
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