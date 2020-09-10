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

/* Escriba un programa que reciba por línea de comandos un Puerto y una IP. El programa
debe aceptar una única conexión e imprimir en stdout la sumatoria de los enteros recibidos
en cada paquete. Un paquete está definido como una sucesión de números recibidos como
texto, en decimal, separados por comas y terminado con un signo igual (ej: "27,12,32="). Al
recibir el texto 'FIN' debe finalizar el programa ordenadamente liberando los recursos. */

#define BUF_LEN 1024

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
    char exit_str[] = "FIN";
    size_t exit_len = strlen(exit_str);
    char buffer[BUF_LEN] = {0};
    char aux[BUF_LEN] = {0};
    size_t pos = 0;
    size_t received = 0;
    long sum = 0;
    val = 0;

    bool salir = false;
    while (!salir && (received = recv(peer, buffer, BUF_LEN, 0)) > 0) {
        for (size_t i = 0; i < received; i++) {
            if (pos == 3 && strncmp(aux, exit_str, exit_len) == 0) {
                salir = true;
                break;
            }

            switch (buffer[i]) {
                case '=': {
                    // sumamos el ultimo, imprimimos y reseteamos
                    aux[pos] = '\0';
                    sum += atoi(aux); 
                    printf("Suma: %ld\n", sum);
                    sum = 0;
                    pos = 0;
                    break;
                }

                case ',': {
                    // sumamos el numero
                    aux[pos] = '\0';
                    sum += atoi(aux); 
                    pos = 0;
                    break;
                }

                case '\n': {
                    // ignoramos los \n
                    break;
                }

                default: {
                    // agregamos el caracter
                    if (pos == BUF_LEN) exit(1);
                    aux[pos++] = buffer[i];
                }
            }            
        }
    }

    // Fin del ejercicio
    shutdown(peer, SHUT_RDWR);
    close(peer);
    shutdown(skt, SHUT_RDWR);
    close(skt);
    freeaddrinfo(result);
    return 0;
}