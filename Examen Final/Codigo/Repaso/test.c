#define _POSIX_C_SOURCE 200112L
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

// includes de C
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buffer[1024];
    if (!fgets(buffer, 1024, stdin)) {
        return 1;
    }

    fprintf(stderr, "[%s]\n", buffer);

    return 0;
}