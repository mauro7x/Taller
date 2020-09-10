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

#define BUF_LEN 1024
#define MAX_LEN (2*(BUF_LEN))

/* Escriba un programa (desde la inicialización hasta la liberación de los
recursos) que reciba paquetes de texto delimitados por corchetes angulares
(<...>) y los imprima completos por pantalla. Al recibir un paquete vacío (<>)
debe cerrarse ordenadamente. No considere errores. */

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

    char buffer[BUF_LEN];
    char package[MAX_LEN];
    size_t pos = 0;
    ssize_t received;
    bool salir = false;

    while (!salir && (received = recv(peer, buffer, BUF_LEN, 0)) > 0) {
        for (size_t i = 0; i < received; i++) {
            if (buffer[i] == '\n') {
                continue;
            } else if (buffer[i] == '>') {
                if (pos == 1 && package[0] == '<') {
                    salir = true;
                    break;
                }

                package[pos] = '\0';
                printf("%s\n", &package[1]);
                pos = 0;
            } else {
                package[pos++] = buffer[i];
            }
        }
    }

    shutdown(peer, SHUT_RDWR);
    close(peer);
    shutdown(skt, SHUT_RDWR);
    close(skt);
    freeaddrinfo(result);
    return 0;
}