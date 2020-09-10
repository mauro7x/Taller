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

/* Consigna. */

int main(int argc, char *argv[]) {
    const char *port = "8080";

    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(0, port, &hints, &result);

    int skt = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (skt < 0) {
        return 1;
    }

    int val = 1;
    setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    bind(skt, result->ai_addr, result->ai_addrlen);
    listen(skt, 1);
    int peer = accept(skt, NULL, NULL);
    
    // Ejercicio

    // ...

    // Fin del ejercicio

    shutdown(peer, SHUT_RDWR);
    close(peer);
    shutdown(skt, SHUT_RDWR);
    close(skt);
    freeaddrinfo(result);
    return 0;
}