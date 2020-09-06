#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
Escriba un programa ISO C que procese el archivo de texto a.txt sobre sí mismo.
El sistema debe recibir dos cadenas por línea de comando: clave y valor. El
procesamiento consiste en recorrer el archivo a.txt y reemplazar todas las
ocurrencias de clave por el contenido de valor. Ej de ejecución:

./programa CONSTANTE 1
./programa MSG "Hola mundo"
*/

#define ERROR(msg)                                                    \
    fprintf(stderr, "error in %s:%d: %s\n", __FILE__, __LINE__, msg); \
    exit(1)

#define NEED_TO_EXPAND(val) ((((val) % 5) == 1) && (val != 1))

// ejercicio de expandir (key < value)
void expandir(FILE* fp, const char* key, const char* value);

// ejercicio de truncar (key >= value)
void truncar(FILE* fp, const char* key, const char* value);

// funciones auxiliares
void armar_archivo(const char* filename);

int leer_c(FILE* fp, long* offset);
int escribir_c(int c, FILE* fp, long* offset);
int escribir_palabra(const char* word, size_t size, FILE* fp, long* offset);

int leer_c_reversa(FILE* fp, long* offset);
int escribir_c_reversa(int c, FILE* fp, long* offset);
int escribir_palabra_reversa(const char* word, size_t rewind, FILE* fp,
                             long* offset);

void leer_reversa(void* ptr, size_t size, size_t nmemb, FILE* fp, long* offset);
void escribir_reversa(const void* ptr, size_t size, size_t nmemb, FILE* fp,
                      long* offset);

int main(int argc, char* argv[]) {
    const char* filename = "a.txt";
    armar_archivo(filename);

    if (argc != 3) {
        ERROR("parametros incorrectos (<key> <value>)");
    }

    FILE* fp = fopen(filename, "rt+");
    if (!fp) {
        ERROR("no se pudo abrir el archivo");
    }

    const char* key = argv[1];
    const char* value = argv[2];

    if (strlen(key) < strlen(value)) {
        expandir(fp, key, value);
    } else {
        truncar(fp, key, value);
    }

    fclose(fp);
    return 0;
}

void expandir(FILE* fp, const char* key, const char* value) {
    // Estrategia de resolución: primero recorremos el archivo para detectar
    // cuantas expansiones hay que realizar y así calcular el tamaño final.
    // Luego, realizamos las expansiones recorriendo el archivo de atrás para
    // adelante.

    size_t key_len = strlen(key);
    size_t value_len = strlen(value);

    char* buffer = (char*)malloc(key_len + 1);
    memset(buffer, 0, key_len + 1);

    size_t final_bytes = 0;
    size_t diferencia_len = value_len - key_len;
    size_t expansiones = 0;
    long seek_escritura = 0;
    long seek_lectura = 0;
    int c;
    bool inicio = true;
    size_t pos = 0;

    // DETECTAMOS EXPANSIONES NECESARIAS

    while ((c = leer_c(fp, &seek_lectura)) != EOF) {
        final_bytes++;

        if (inicio) {
            buffer[pos] = c;
            if (++pos == key_len) {
                inicio = false;
            }

            if (strncmp(buffer, key, key_len) == 0) {
                expansiones++;
                inicio = true;
                pos = 0;
                memset(buffer, 0, key_len + 1);
            }

            continue;
        }

        for (size_t i = 0; i < (key_len - 1); i++) {
            buffer[i] = buffer[i + 1];
        }

        buffer[key_len - 1] = c;

        if (strncmp(buffer, key, key_len) == 0) {
            expansiones++;
            inicio = true;
            pos = 0;
            memset(buffer, 0, key_len + 1);
        }
    }

    final_bytes += (diferencia_len * expansiones);
    ftruncate(fileno(fp), final_bytes);

    // EXPANDIMOS
    fseek(fp, 0, SEEK_END);
    seek_escritura = ftell(fp);

    inicio = true;
    pos = key_len - 1;
    memset(buffer, 0, key_len + 1);

    while ((c = leer_c_reversa(fp, &seek_lectura)) != EOF) {
        if (inicio) {
            buffer[pos] = c;
            if (pos-- == 0) {
                inicio = false;
            }

            if (strncmp(buffer, key, key_len) == 0) {
                escribir_palabra_reversa(value, (value_len - key_len), fp,
                                         &seek_escritura);
                inicio = true;
                pos = key_len - 1;
                memset(buffer, 0, key_len + 1);
            } else {
                escribir_c_reversa(c, fp, &seek_escritura);
            }

            continue;
        }

        for (size_t i = (key_len - 1); i != 0; i--) {
            buffer[i] = buffer[i - 1];
        }

        buffer[0] = c;

        if (strncmp(buffer, key, key_len) == 0) {
            escribir_palabra_reversa(value, (value_len - key_len), fp,
                                     &seek_escritura);
            inicio = true;
            pos = key_len - 1;
            memset(buffer, 0, key_len + 1);
        } else {
            escribir_c_reversa(c, fp, &seek_escritura);
        }
    }

    free(buffer);
}

void truncar(FILE* fp, const char* key, const char* value) {
    size_t key_len = strlen(key);
    size_t value_len = strlen(value);

    char* buffer = (char*)malloc(key_len + 1);
    memset(buffer, 0, key_len + 1);

    size_t final_bytes = 0;
    long seek_escritura = 0;
    long seek_lectura = 0;
    int c;
    bool inicio = true;
    size_t pos = 0;

    while ((c = leer_c(fp, &seek_lectura)) != EOF) {
        final_bytes++;

        if (inicio) {
            buffer[pos] = c;
            if (++pos == key_len) {
                inicio = false;
            }

            if (strncmp(buffer, key, key_len) == 0) {
                final_bytes -= (key_len - value_len);
                seek_escritura -= (key_len - 1);
                escribir_palabra(value, value_len, fp, &seek_escritura);
                inicio = true;
                pos = 0;
                memset(buffer, 0, key_len + 1);
            } else {
                escribir_c(c, fp, &seek_escritura);
            }

            continue;
        }

        for (size_t i = 0; i < (key_len - 1); i++) {
            buffer[i] = buffer[i + 1];
        }

        buffer[key_len - 1] = c;

        if (strncmp(buffer, key, key_len) == 0) {
            final_bytes -= (key_len - value_len);
            seek_escritura -= (key_len - 1);
            escribir_palabra(value, value_len, fp, &seek_escritura);
            inicio = true;
            pos = 0;
            memset(buffer, 0, key_len + 1);
        } else {
            escribir_c(c, fp, &seek_escritura);
        }
    }

    free(buffer);
    ftruncate(fileno(fp), final_bytes);
}

void armar_archivo(const char* filename) {
    FILE* fp = fopen(filename, "wt");
    if (!fp) {
        ERROR("no se pudo abrir el archivo");
    }

    fputs(
        "hola como estas?\ntodo bien?\ncomo va tu vida?\na mi me gusta comer, "
        "como de todo.",
        fp);

    fclose(fp);
}

int leer_c(FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    int out = fgetc(fp);
    *offset = ftell(fp);
    return out;
}

int escribir_c(int c, FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    int out = fputc(c, fp);
    *offset = ftell(fp);
    return out;
}

int escribir_palabra(const char* word, size_t size, FILE* fp, long* offset) {
    fseek(fp, *offset, SEEK_SET);
    (*offset) += size;
    return fputs(word, fp);
}

int leer_c_reversa(FILE* fp, long* offset) {
    if (*offset == 0) {
        return EOF;
    }
    (*offset)--;
    fseek(fp, *offset, SEEK_SET);
    return fgetc(fp);
}

int escribir_c_reversa(int c, FILE* fp, long* offset) {
    (*offset)--;
    fseek(fp, *offset, SEEK_SET);
    return fputc(c, fp);
}

int escribir_palabra_reversa(const char* word, size_t rewind, FILE* fp,
                             long* offset) {
    (*offset) -= (rewind + 1);
    fseek(fp, *offset, SEEK_SET);
    return fputs(word, fp);
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