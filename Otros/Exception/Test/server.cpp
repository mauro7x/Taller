#include <stdio.h>

#include <string>

#include "ClosedSocketException.h"
#include "Exception.h"
#include "SocketWrapper.h"

int main(int argc, char* argv[]) {
    try {
        // code
        if (argc != 2) {
            throw Exception("Error en los argumentos.");
        }

        std::string port = argv[1];

        SocketWrapper accepter(port, 10);

        accepter.close();

        SocketWrapper peer = accepter.accept();

        // do stuff

        peer.shutdown();
        peer.close();
        // accepter.shutdown();
        // accepter.close();

    } catch (const ClosedSocketException& e) {
        fprintf(stderr, "CLOSED SOCKET EXCEPTION! %s\n", e.what());
        return 1;
    } catch (const Exception& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    } catch (...) {
        fprintf(stderr, "Unknown error.\n");
        return 1;
    }

    return 0;
}
