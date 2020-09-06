#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    FILE* f = fopen("a.txt", "w+");
    char buffer[] = "hola como estas";
    fwrite(buffer, 1, sizeof(buffer), f);
    fclose(f);
    return 0;
}