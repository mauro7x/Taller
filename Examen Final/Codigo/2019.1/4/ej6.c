#define _POSIX_C_SOURCE 200112L

// includes para sockets (de UNIX)
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// includes
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 1024

/* Escriba un programa que reciba por línea de comandos un Puerto y una IP. El
 * programa debe aceptar una unica conexión e imprimir en stdout todo lo
 * recibido. Al recibir el texto "FIN" debe finalizar el programa sin imprimir
 * dicho texto. */

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "bad arguments. usage: %s <ip> <port>\n", argv[0]);
        return 1;
    }

    const char* ip = argv[1];
    const char* port = argv[2];

    // bind
    struct addrinfo hints;
    struct addrinfo *addresses, *ptr;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(ip, port, &hints, &addresses);
    int skt;
    for (ptr = addresses; ptr != NULL; ptr = ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (skt != -1) {
            break;
        }
    }

    int val = 1;
    setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    bind(skt, ptr->ai_addr, ptr->ai_addrlen);

    // listen
    listen(skt, 1);

    // accept
    int peer_skt = accept(skt, NULL, NULL);

    // ej
    char buffer[BUF_LEN];
    char exit_string[] = "FIN";
    bool salir = false;
    size_t recibidos;

    while (!salir) {
        recibidos = recv(peer_skt, buffer, BUF_LEN - 1, 0);
        if (!recibidos) {
            salir = true;
            break;
        }

        buffer[recibidos] = '\0';
        if (strncmp(buffer, exit_string, sizeof(exit_string) - 1) == 0) {
            salir = true;
        } else {
            fprintf(stdout, "%s", buffer);
        }
    }

    // liberar
    shutdown(peer_skt, SHUT_RDWR);
    shutdown(skt, SHUT_RDWR);
    close(peer_skt);
    close(skt);
    freeaddrinfo(addresses);
    return 0;
}
