#define _POSIX_C_SOURCE 200112L

// includes para sockets (de UNIX)
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// includes
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAQUETE 1024

/* Escriba un programa que reciba por línea de comandos un Puerto y una IP. El
 * programa debe aceptar una única conexión e imprimir en stdout la sumatoria de
 * los enteros recibidos en cada paquete. Un paquete está definido como una
 * sucesión de números recibidos como texto, en decimal, separados por comas y
 * terminado con un signo igual (ej: "27,12,32="). Al recibir el texto "FIN"
 * debe finalizar el programa ordenadamente liberando los recursos. */

void procesar_paquete(const char paquete[MAX_PAQUETE], size_t len);

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

    bind(skt, ptr->ai_addr, ptr->ai_addrlen);

    // 2) Listen
    listen(skt, 1);

    // 3) Accept
    int peerskt = accept(skt, NULL, NULL);

    // 4) Ejercicio particular
    bool salir = false;
    ssize_t bytes_recibidos;
    char paquete[MAX_PAQUETE];
    char exit_request[] = "FIN";
    size_t len_exit_request = strlen(exit_request);
    memset(paquete, '\0', MAX_PAQUETE);

    while (!salir) {
        bytes_recibidos = recv(peerskt, paquete, MAX_PAQUETE, 0);
        if (!bytes_recibidos) {
            salir = true;
            continue;
        }

        if (strncmp(paquete, exit_request, len_exit_request) == 0) {
            salir = true;
            continue;
        }

        procesar_paquete(paquete, bytes_recibidos);
    }

    // 5) Liberar
    shutdown(peerskt, SHUT_RDWR);
    shutdown(skt, SHUT_RDWR);
    close(skt);
    close(peerskt);
    freeaddrinfo(result);
    return 0;
}

void procesar_paquete(const char paquete[MAX_PAQUETE], size_t len) {
    char aux[MAX_PAQUETE];
    size_t aux_pos = 0;
    long sum = 0;
    long val;
    char c;

    for (size_t i = 0; i < len; i++) {
        c = paquete[i];
        switch (c) {
            case ',': {
                aux[aux_pos] = '\0';
                val = atoi(aux);
                sum += val;
                aux_pos = 0;
                break;
            }

            case '=': {
                aux[aux_pos] = '\0';
                val = atoi(aux);
                sum += val;
                aux_pos = 0;
                fprintf(stdout, "Suma: %ld\n", sum);
                sum = 0;
                break;
            }

            case '\n': {
                break;
            }

            default: {
                aux[aux_pos] = paquete[i];
                aux_pos++;
                break;
            }
        }
    }
}