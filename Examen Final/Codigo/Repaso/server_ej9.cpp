#include <iostream>

// Mis clases
#include "Socket.h"

int main(int argc, char* argv[]) {
    const char* port = (argc > 1) ? argv[1] : "8080";

    try {
        Socket skt;
        skt.listen(port, 1);

        Socket peer = skt.accept();

    } catch (const SocketException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}