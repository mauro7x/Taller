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
    fp = fopen(FILEPATH, "w+");

    if (fp == NULL) {
        fprintf(stderr, "error abriendo el archivo.\n");
        return 1;
    }

    // asumo que son positivos
    uint16_t a, b, c, d;
    a = 3;
    b = 5;
    c = 7;
    d = 9;
    fwrite(&a, sizeof(a), 1, fp);
    fwrite(&b, sizeof(b), 1, fp);
    fwrite(&c, sizeof(c), 1, fp);
    fwrite(&d, sizeof(d), 1, fp);
    
    fclose(fp);
    return 0;
}

// definiciones
