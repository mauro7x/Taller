#include <iostream>
#include <string>

// Mis clases
#include "Socket.h"

/* Declare la clase Socket y realice un programa que la emplee para realizar
conexiones con un servidor externo. Dicho programa recibe una dirección IP por
argumento y establece una conexión al puerto 80 de dicha dirección. Luego, debe
enviar el mensaje "GET / HTTP/1.1\n", esperar la respuesta, imprimirla por
consola y cerrar la conexión. Se considera como fin de
respuesta la detección de la secuencia "\n\n". */

int main(int argc, char* argv[]) {
    const char* host = argv[1];
    const char* port = "8080";

    try {
        Socket skt;
        if (!skt.connect(host, port)) {
            return 1;
        }

        std::string msg = "GET / HTTP/1.1\n";
        size_t sent = skt.send_all(msg.data(), msg.size(), MSG_NOSIGNAL);
        if (sent != msg.size()) {
            std::cerr << "socket was closed" << '\n';
            return 1;
        }

        char buffer[BUFSIZ];
        size_t received;
        char last_c = 0;
        bool salir = false;

        while (!salir && (received = skt.recv(buffer, BUFSIZ, 0))) {
            for (size_t i = 0; i < received; i++) {
                if (buffer[i] == '\n' && last_c == '\n') {
                    salir = true;
                } else {
                    std::cout << buffer[i];
                }

                last_c = buffer[i];
            }
        }

    } catch (const SocketException& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}