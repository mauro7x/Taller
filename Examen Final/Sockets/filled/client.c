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
    if (argc != 3) {
        fprintf(stderr, "usage: %s <ip> <port>\n", argv[0]);
        return 1;
    }

    const char* ip = argv[1];
    const char* port = argv[2];

    // getaddrinfo
    struct addrinfo hints;
    struct addrinfo *result, *ptr;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    getaddrinfo(ip, port, &hints, &result);

    // Connect
    int skt;
    bool connected = false;
    for (ptr = result; ptr != NULL && !connected; ptr = ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (skt < 0) {
            continue;
        }
        
        if (connect(skt, ptr->ai_addr, ptr->ai_addrlen)) {
            close(skt);   
        } else {
            connected = true;
        }
    }

    if (!connected) {
        fprintf(stderr, "out of addresses to connect to\n");
        return 1;
    }

    // Ejercicio particular
    // ...

    // Liberar recursos
    shutdown(skt, SHUT_RDWR);
    close(skt);
    freeaddrinfo(result);

    return 0;
}