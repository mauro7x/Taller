#include <stdio.h>

#include <string>

#include "ClosedSocketException.h"
#include "Exception.h"
#include "SocketWrapper.h"

int main(int argc, char* argv[]) {
    try {
        // code
        if (argc != 3) {
            throw Exception("Error en los argumentos.");
        }

        std::string hostname = argv[1];
        std::string port = argv[2];

        SocketWrapper socket(hostname, port);

        // do stuff

        socket.shutdown();
        socket.close();

    } catch (const ClosedSocketException& e) {
        fprintf(stderr, "%s\n", e.what());
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
