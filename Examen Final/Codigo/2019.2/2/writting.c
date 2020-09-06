// includes
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

// defines

// declaraciones

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "uso esperado: %s <filename>\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "error abriendo archivo\n");
        return 1;
    }

    uint16_t a = 2, b = 4, c = 6, d = 8;
    a = htons(a);
    b = htons(b);
    c = htons(c);
    d = htons(d);

    fwrite(&a, sizeof(a), 1, fp);
    fwrite(&b, sizeof(b), 1, fp);
    fwrite(&c, sizeof(c), 1, fp);
    fwrite(&d, sizeof(d), 1, fp);

    fclose(fp);
    return 0;
}

// definiciones
