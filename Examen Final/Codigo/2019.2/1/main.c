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
        if (!(num % 3)) {
            // duplicar
            num *= 2;
            s = fseek(fp, -sizeof(num), SEEK_CUR);
            if (s < 0) {
                fclose(fp);            
                return 1;
            }

            s = fwrite(&num, sizeof(num), 1, fp);
            if (s <= 0) {
                fclose(fp);            
                return 2;
            }
        }

        read = fread(&num, sizeof(uint16_t), 1, fp);
    }

    fclose(fp);
    return 0;
}

// definiciones
