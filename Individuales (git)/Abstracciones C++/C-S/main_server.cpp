#include <iostream>

#include "Socket.h"
#include "Exception.h"

#define MAX_CLIENTS_IN_QUEUE 10

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>\n";
        return -1;
    }

    std::string port = argv[1];

    try {
        std::cout << "Trying to open server...\n";
        Socket skt(port, MAX_CLIENTS_IN_QUEUE);
        std::cout << "Server open!\n";

        std::cout << "Listening...\n";
        skt.accept();
        std::cout << "A client has been accepted.\n";

        std::cout << "Trying to shutdown...\n";
        skt.shutdown();
        std::cout << "Server has been shutdown.\n";

    } catch(Exception& e) {
        std::cerr << e.what() << '\n';
        return e.getErrorCode();
    }
    return 0;
}