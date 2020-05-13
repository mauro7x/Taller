#include <iostream>

#include "Socket.h"
#include "Exception.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <hostname> <port>\n";
        return -1;
    }

    std::string hostname = argv[1];
    std::string port = argv[2];

    try {
        std::cout << "Trying to connect to server...\n";
        Socket skt(hostname, port);
        std::cout << "Connected!\n";

        std::cout << "Trying to shutdown...\n";
        skt.shutdown();
        std::cout << "Client has been shutdown.\n";

    } catch(Exception& e) {
        std::cerr << e.what() << '\n';
        return e.getErrorCode();
    }
    return 0;
}