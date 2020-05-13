#include <iostream>
#include <vector>
#include <mutex>

#include "Socket.h"
#include "Exception.h"
#include "Thread.h"

#define MAX_CLIENTS_IN_QUEUE 10
#define N_CLIENTS 2


std::mutex m;



//-----------------

class Client : public Thread {
    private:
        Socket peer;
    public:
        Client(int fd) : peer(fd) {}

        virtual void run() override {
            std::string msg;
            peer >> msg;

            { // Critical section
                m.lock();
                std::cout << "Recibí: " << msg << "\n";
                m.unlock();
            }
        }

        virtual ~Client() {
            peer.shutdown();
        }
};


//-----------------

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>\n";
        return -1;
    }

    std::string port = argv[1];
    std::vector<Thread*> clients;
    clients.reserve(N_CLIENTS);

    std::string msg;

    try {
        std::cout << "Trying to open server...\n";
        Socket skt(port, MAX_CLIENTS_IN_QUEUE);
        std::cout << "Server open!\n";

        std::cout << "Listening...\n";
        for (unsigned int i = 0; i < N_CLIENTS; i++) {
            clients.push_back(new Client(skt.accept()));;
        }

        std::cout << "Running...\n";
        for (unsigned int i = 0; i < N_CLIENTS; i++) {
            clients[i]->start();
        }
        
        for (unsigned int i = 0; i < N_CLIENTS; i++) {
            clients[i]->join();
            delete clients[i];
        }

        std::cout << "Trying to shutdown...\n";     
        skt.shutdown();
        std::cout << "Server has been shutdown.\n";

    } catch(Exception& e) {
        std::cerr << e.what() << '\n';
        return e.getErrorCode();
    }
    return 0;
}