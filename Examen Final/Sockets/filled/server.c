// Includes para sockets POSIX
#define _POSIX_C_SOURCE 200112L
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Includes propios de C
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // Chequeo de parámetros
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }

    const char* port = argv[1];

    // getaddrinfo
    struct addrinfo hints;
    struct addrinfo* result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(0, port, &hints, &result);

    // Socket accepter
    int skt =
        socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    // Re-use addr
    int val = 1;
    setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    // Bind
    bind(skt, result->ai_addr, result->ai_addrlen);

    // Listen
    listen(skt, 1);

    // Accept
    int peer = accept(skt, NULL, NULL);

    // Ejercicio particular
    // ...

    // Liberar recursos
    shutdown(peer, SHUT_RDWR);
    close(peer);
    shutdown(skt, SHUT_RDWR);
    close(skt);
    freeaddrinfo(result);

    return 0;
}