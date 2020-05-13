#include "Socket.h"

//-----------------------------------------------------------------------------
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <unistd.h>

#include "Exception.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Métodos privados

void Socket::_setServerAddress(const std::string& port, addrinfo** address) {
    addrinfo hints;
    
    // Filtros que nos interesan:
    hints.ai_family = AF_INET;          // IPv4
    hints.ai_socktype = SOCK_STREAM;    // TCP
    hints.ai_flags = AI_PASSIVE;        // Servidor
    hints.ai_protocol = 0;

    // Inicializamos en 0 el resto de los valores:
    hints.ai_addr = NULL;
    hints.ai_addrlen = 0;
    hints.ai_canonname = NULL;
    hints.ai_next = NULL;

    if (::getaddrinfo(0, &port[0], &hints, address)) {
        throw Exception(GET_ADDRESS_SKT_ERROR, "Error in function: "
                        "Socket::_setServerAddres()");
    }
}


void Socket::_setClientAddresses(const std::string& hostname,
                                 const std::string& port,
                                 addrinfo** addresses) {
    addrinfo hints;
    
    // Filtros que nos interesan:
    hints.ai_family = AF_INET;          // IPv4
    hints.ai_socktype = SOCK_STREAM;    // TCP
    hints.ai_flags = 0;                 // Cliente
    hints.ai_protocol = 0;

    // Inicializamos en 0 el resto de los valores:
    hints.ai_addr = NULL;
    hints.ai_addrlen = 0;
    hints.ai_canonname = NULL;
    hints.ai_next = NULL;

    if (::getaddrinfo(&hostname[0], &port[0], &hints, addresses)) {
        throw Exception(GET_ADDRESS_SKT_ERROR, "Error in function: "
                        "Socket::_setClientAddresses()");
    }
}


void Socket::_setFd(addrinfo* address, addrinfo* all_addresses) {
    fd = ::socket(address->ai_family, address->ai_socktype,
                  address->ai_protocol);
                           
    if (fd == -1) {
        ::freeaddrinfo(all_addresses);
        throw Exception(SET_FD_SKT_ERROR, "Error in function: "
                        "Socket::_setFd()");
    } else {
        fd_valid = true;
    }
}


void Socket::_fixTimeWait(addrinfo* address) {
    int val = 1;
    if (::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val))) {
        ::freeaddrinfo(address);
        throw Exception(FIX_TW_SKT_ERROR, "Error in function: "
                        "Socket::_fixTimeWait()");
    }
}


void Socket::_bind(addrinfo* address) {
    int s;
    s = bind(fd, address->ai_addr, address->ai_addrlen);
    ::freeaddrinfo(address);

    if (s == -1) {
        throw Exception(BIND_SKT_ERROR, "Error in function: "
                        "Socket::_bind()");
    }
}


void Socket::_listen(const int& max_queued_clients){
    if (listen(fd, max_queued_clients)) {
        throw Exception(LISTEN_SKT_ERROR, "Error in function: "
                        "Socket::_listen()");
    }
}


void Socket::_tryToConnectTo(addrinfo* addresses) {
    bool connected = false;
    addrinfo* ptr;
    try {
        for (ptr = addresses; ((ptr != NULL) && (connected == false));
             ptr = ptr->ai_next) {
            _setFd(ptr, addresses);
            if (::connect(fd, ptr->ai_addr, ptr->ai_addrlen)) {
                _closeFdIfValid();
            } else {
                connected = true;
            }
        }

        ::freeaddrinfo(addresses);
        if (!connected) {
            throw Exception(CONNECT_SKT_ERROR, "Error in function: "
                            "Socket::_tryToConnectTo(). "
                            "Client ran out of addresses to try.");
        }
    } catch(const Exception& e) {
        throw e;
    }
}


void Socket::_closeFdIfValid() {
    if (fd_valid) {
        fd_valid = false;
        close(fd);
    }
}


//-----------------------------------------------------------------------------
// API Pública

Socket::Socket(const std::string& port, const int& max_queued_clients) {
    // Método para el servidor. Abrir servidor.
    fd_valid = false;
    addrinfo* address;
    try {
        _setServerAddress(port, &address);
        _setFd(address, address);
        _fixTimeWait(address);
        _bind(address);
        _listen(max_queued_clients);
    } catch(const Exception& e) {
        throw e;
    }
}


Socket::Socket(const int& fd) : fd(fd), fd_valid(true) {}


Socket::Socket(const std::string& hostname, const std::string& port) {
    // Método para el cliente. Conectarse a un servidor.
    addrinfo* addresses;
    try {
        _setClientAddresses(hostname, port, &addresses);
        _tryToConnectTo(addresses);
    } catch(const Exception& e) {
        throw e;
    }
}


Socket::Socket(Socket&& other) {
    this->fd = std::move(other.fd);
    this->fd_valid = std::move(other.fd_valid);
}


Socket& Socket::operator=(Socket&& other) {
    this->fd = std::move(other.fd);
    this->fd_valid = std::move(other.fd_valid);
    return *this;
}


int Socket::accept() {
    int peer_socket = ::accept(fd, NULL, NULL);
    if (peer_socket == -1) {
        throw Exception(ACCEPT_SKT_ERROR, "Error in function: "
                        "Socket::accept()");
    }
    return peer_socket;
}


ssize_t Socket::send(const char* source, const ssize_t& len) {
    ssize_t total_sent = 0;
    ssize_t last_sent = 0;

    while (total_sent < len) {
        last_sent = ::send(fd, &source[total_sent], len - total_sent,
                           MSG_NOSIGNAL);

        if (last_sent == -1) {
            throw Exception(SENT_SKT_ERROR, "Error in function: "
                            "Socket::send()");
        } else if (last_sent == 0) {
            return 0;
        } else {
            total_sent += last_sent;
        }
    }

    return total_sent;
}


/** SUPER EN ALPHA*/
ssize_t Socket::operator<<(std::string& msg) {
    try {
        ssize_t sent;
        sent = send(msg.c_str(), msg.size()+1); //enviamos \0
        return sent;
    } catch(const Exception& e) {
        throw e;
    }
}


/** SUPER EN ALPHA*/
ssize_t Socket::operator>>(std::string& msg) {
    try {
        msg.clear();
        char received_char;
        ssize_t received = 0;

        received += recv(&received_char, 1);
        while (received_char != '\0') {
            msg += received_char;
            received += recv(&received_char, 1);
        }
        msg.shrink_to_fit();
        return received;

    } catch(const Exception& e) {
        throw e;
    }
}


ssize_t Socket::recv(char* buffer, const ssize_t& len) {
    int total_received = 0;
    int last_received = 0;
    
    while (total_received < len) {
        last_received = ::recv(fd, &buffer[total_received],
                               len - total_received, 0);

        if (last_received == -1) {
            throw Exception(RECV_SKT_ERROR, "Error in function: "
                            "Socket::recv()");
        } else if (last_received == 0) {
            return 0;
        } else {
            total_received += last_received;
        }
    }

    return total_received;
}


void Socket::shutdown(const int& channel) {
    if (fd_valid) {
        if (::shutdown(fd, channel)) {
            throw Exception(SHUTDOWN_SKT_ERROR, "Error in function: "
                            "Socket::shutdown()");
        }
    }
}


Socket::~Socket() {
    _closeFdIfValid();
}


//-----------------------------------------------------------------------------
