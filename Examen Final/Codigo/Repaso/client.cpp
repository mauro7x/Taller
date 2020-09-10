#include <iostream>

// Mis clases
#include "Socket.h"

int main(int argc, char* argv[]) {
    const char* host = (argc > 1) ? argv[1] : "localhost";
    const char* port = (argc > 2) ? argv[2] : "8080";

    try {
        Socket skt;
        if (skt.connect(host, port)) {
            return 1;
        }

        // connected

    } catch (const SocketException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}