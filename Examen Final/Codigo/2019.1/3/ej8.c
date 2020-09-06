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
#define MAX_PAQUETE (2 * BUF_LEN)

/* Escriba un programa (desde la inicialización hasta la liberación de los
 * recursos) que reciba paquetes de la forma [nnn+nn+....+nnnn] (numeros
 * separados por +, encerrados entre corchetes) e imprima el resultado de la
 * suma de cada paquete por pantalla. Al recibir un paquete vacío ("[]") debe
 * cerrarse ordenadamente. No considere errores. */

#define ERROR(msg, ...)                \
    fprintf(stderr, msg, __VA_ARGS__); \
    exit(1)

void procesar_paquete(char* package);

int main(int argc, char* argv[]) {
    char* ip = argv[1];
    char* port = argv[2];

    // 1) Bind
    struct addrinfo hints;
    struct addrinfo *result, *ptr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(ip, port, &hints, &result);
    int skt;
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (skt != -1)
            break;
    }

    int val = 1;
    setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    bind(skt, ptr->ai_addr, ptr->ai_addrlen);

    // 2) Listen
    listen(skt, 1);

    // 3) Accept
    int peerskt = accept(skt, NULL, NULL);

    // 4) Ejercicio
    bool salir = false;
    char buffer[BUF_LEN];
    char paquete[MAX_PAQUETE];
    size_t pos_paquete = 0;
    ssize_t bytes_recibidos;
    char c;

    while (!salir) {
        bytes_recibidos = recv(peerskt, buffer, BUF_LEN, 0);
        for (size_t i = 0; i < bytes_recibidos; i++) {
            c = buffer[i];
            if (c == '\n') {
                continue;
            }

            paquete[pos_paquete] = c;

            if (c == ']') {
                // fin de paquete
                if (strncmp(paquete, "[]", 2) == 0) {
                    salir = true;
                    break;
                }

                paquete[pos_paquete] = '\0';
                procesar_paquete(&paquete[1]);

                // reiniciar
                pos_paquete = 0;
            } else {
                pos_paquete++;
            }
        }
    }

    // 5) Liberar
    shutdown(peerskt, SHUT_RDWR);
    shutdown(skt, SHUT_RDWR);
    close(skt);
    close(peerskt);
    freeaddrinfo(result);
    return 0;
}

void procesar_paquete(char* paquete) {
    fprintf(stderr, "paquete recibido para procesar: %s\n", paquete);
    size_t len = strlen(paquete);

    int sum = 0;
    char num[MAX_PAQUETE];
    size_t num_pos = 0;
    char c;

    for (size_t i = 0; i < len; i++) {
        c = paquete[i];
        num[num_pos++] = c;
        if (c == '+') {
            num[num_pos - 1] = '\0';
            sum += strtol(num, NULL, 10);
            num_pos = 0;
        }
    }

    num[num_pos] = '\0';
    sum += strtol(num, NULL, 10);

    fprintf(stderr, "SUMA: %d\n", sum);
}