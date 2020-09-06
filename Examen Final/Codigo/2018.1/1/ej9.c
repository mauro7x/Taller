#define _POSIX_C_SOURCE 200112L
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Escriba un programa que reciba paquetes de 10 bytes por el puerto TCP 815 y
los imprima por pantalla. Al recibir el byte 0xff debe cerrarse ordenadamente.
No considere errores. */

#define LEN_PAQUETE 10

ssize_t recv_all(int skt_fd, char* buf, size_t len, int flags) {
    ssize_t received = 0;
    ssize_t last_received = 0;
    while (received < len) {
        last_received = recv(skt_fd, &buf[received], len-received, flags);
        if (last_received < 0) {
            return last_received;
        } else if (last_received == 0) {
            return 0;
        } else {
            received += last_received;
        }
    }

    return received;
}

bool salir(char buf[LEN_PAQUETE]) {
    for (size_t i = 0; i < LEN_PAQUETE; i++) {
        if (buf[i] == 'Q') {
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    const char* service = "8080";

    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(0, service, &hints, &result);

    int skt = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    int val = 1;
    setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    bind(skt, result->ai_addr, result->ai_addrlen);
    listen(skt, 1);
    int peer = accept(skt, NULL, NULL);

    char buf[LEN_PAQUETE];
    while (recv_all(peer, buf, LEN_PAQUETE, 0) > 0) {
        if (salir(buf)) {
            break;
        }

        printf("paquete recibido: [%s]\n", buf);
    }

    shutdown(peer, SHUT_RDWR);
    close(peer);
    shutdown(skt, SHUT_RDWR);
    close(skt);
    freeaddrinfo(result);
    return 0;
}
