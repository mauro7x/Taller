#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

    char* buff = "hola mauris tranquilo";
    size_t len = strlen(buff);

    char* temp = malloc(sizeof(char) * (len+1));

    strcpy(temp, buff);

    printf("%s", temp);

    free(temp);


    return 0;
}
