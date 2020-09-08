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

// Definición de códigos de retorno
enum ret { SUCCESS = 0, BAD_USAGE, GETADDRINFO_ERR, OUT_OF_ADDRESSES,
           SEND_ERR, RECV_ERR };

int main(int argc, char* argv[]) {
    // Definir dirección host y puerto (servicio) objetivo
    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        return BAD_USAGE;
    }

    const char *host = argv[1];
    const char *port = argv[2];

    // Obtener direcciones del servidor con getaddrinfo
    struct addrinfo hints;
    struct addrinfo *result, *ptr;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // AF_INET == IPv4, AF_INET6 == IPv6
    hints.ai_socktype = SOCK_STREAM; // SOCK_STREAM == TCP, SOCK_DGRAM == UDP
    hints.ai_flags = 0; // AI_PASSIVE == Server, 0 == Client
    if (getaddrinfo(host, port, &hints, &result)) {
        return GETADDRINFO_ERR;
    }

    // Iterar sobre las direcciones obtenidas para conectarnos con connect
    int skt;
    bool connected = false;
    for (ptr = result; (ptr != NULL) && (!connected); ptr = ptr->ai_next) {
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

    // Chequear conexión, caso contrario retornar con error
    if (!connected) {
        freeaddrinfo(result); // liberamos recursos
        return OUT_OF_ADDRESSES;
    }

    // Realizar el ejercicio en particular
    // ...

    // Liberar recursos con shutdown, close, y freeaddrinfo
    shutdown(skt, SHUT_RDWR);
    close(skt);
    freeaddrinfo(result);

    return SUCCESS;
}
