// Includes y defines necesarios para utilizar los sockets POSIX
#define _POSIX_C_SOURCE 200112L
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

// Includes propios de C
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Definición de cantidad máxima de conexiones en espera
#define MAX_IN_QUEUE 10

// Definición de códigos de retorno
enum ret { SUCCESS = 0, BAD_USAGE, GETADDRINFO_ERR, SOCKET_ERR, SETSOCKOPT_ERR,
           BIND_ERR, LISTEN_ERR, ACCEPT_ERR, SEND_ERR, RECV_ERR };

int main(int argc, char* argv[]) {
    // Definir puerto en el que escucharemos conexiones
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return BAD_USAGE;
    }

    const char *port = argv[1];

    // Obtener direccion con getaddrinfo
    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // AF_INET == IPv4, AF_INET6 == IPv6
    hints.ai_socktype = SOCK_STREAM; // SOCK_STREAM == TCP, SOCK_DGRAM == UDP
    hints.ai_flags = AI_PASSIVE; // AI_PASSIVE == Server, 0 == Client
    if (getaddrinfo(0, port, &hints, &result)) {
        return GETADDRINFO_ERR;
    }

    // Crear el socket acceptador con socket
    int skt = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (skt < 0) {
        freeaddrinfo(result);
        return SOCKET_ERR;
    }

    // (opcional) Reutilizar dirección con setsockopt
    int val = 1;
    if (setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val))) {
        close(skt);
        freeaddrinfo(result);
        return SETSOCKOPT_ERR;
    }
   
    // Realizar bind al puerto determinado
    if (bind(skt, result->ai_addr, result->ai_addrlen)) {
        close(skt);
        freeaddrinfo(result);
        return BIND_ERR;
    }

    // Realizar listen especificando máximo número de conexiones en espera
    if (listen(skt, MAX_IN_QUEUE)) {
        close(skt);
        freeaddrinfo(result);
        return LISTEN_ERR;
    }

    // A modo de ejemplo, aceptamos una conexión con accept
    int peer = accept(skt, NULL, NULL);
    if (peer < 0) {
        close(skt);
        freeaddrinfo(result);
        return ACCEPT_ERR;
    }

    // Realizar el ejercicio en particular
    // ...

    // Liberar recursos con shutdown, close, y freeaddrinfo
    shutdown(peer, SHUT_RDWR);
    close(peer);
    shutdown(skt, SHUT_RDWR);
    close(skt);
    freeaddrinfo(result);

    return SUCCESS;
}
