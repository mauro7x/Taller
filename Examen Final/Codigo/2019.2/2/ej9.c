// includes
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "uso esperado: %s <filename>\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];
    FILE *fp = fopen(filename, "r+");
    if (!fp) {
        fprintf(stderr, "error abriendo archivo\n");
        return 1;
    }

    long int final_size = 0;

    uint16_t num;
    long diff = 0;

    ssize_t read = fread(&num, sizeof(num), 1, fp);
    while (read > 0) {
        num = ntohs(num);

        if (num % 3) {
            // lo copiamos donde corresponde
            fseek(fp, -(sizeof(num) + diff), SEEK_CUR);
            num = htons(num);
            fwrite(&num, sizeof(num), 1, fp);
            fseek(fp, diff, SEEK_CUR);
            diff = 0;

            final_size += sizeof(num);
        } else {
            diff += sizeof(num);
        }   

        read = fread(&num, sizeof(num), 1, fp);
    }


    ftruncate(fileno(fp), final_size);
    fclose(fp);
    return 0;
}
