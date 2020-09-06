// includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// defines
#define FILEPATH "nros2bytes.dat"

// declaraciones

int main(int argc, char* argv[]) {
    int s;
    FILE *fp;
    fp = fopen(FILEPATH, "r+");

    if (fp == NULL) {
        fprintf(stderr, "error abriendo el archivo.\n");
        return 1;
    }

    // asumo que son positivos
    uint16_t num;
    size_t read = fread(&num, sizeof(uint16_t), 1, fp);
    while (read > 0) {
        printf("%u\n", num);
        read = fread(&num, sizeof(uint16_t), 1, fp);
    }

    fclose(fp);
    return 0;
}

// definiciones
