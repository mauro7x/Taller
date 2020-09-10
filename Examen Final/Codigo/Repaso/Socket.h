#ifndef __SOCKET_H__
#define __SOCKET_H__

// Sockets POSIX
//#define _POSIX_C_SOURCE 200112L
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Otros
#include <string.h>

#include <exception>

class SocketException : public std::exception {
   private:
    std::string msg;

   public:
    SocketException(const char* msg = NULL) {
        this->msg = msg ? msg : "SocketException";
    }

    virtual const char* what() const noexcept {
        return this->msg.data();
    }
};

class Socket {
   private:
    int fd;  // >0 if valid; -1 invalid
    struct addrinfo* addresses;

    Socket(int peer_fd) : fd(peer_fd), addresses(NULL) {}

    void _getaddrinfo(const char* host, const char* port,
                      bool passive = false) {
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = passive ? AI_PASSIVE : 0;

        if (addresses) {
            freeaddrinfo(addresses);
            addresses = NULL;
        }

        if (::getaddrinfo(host ? host : 0, port ? port : 0, &hints,
                          &addresses)) {
            throw SocketException("getaddrinfo");
        }
    }

    void _socket(struct addrinfo* ptr = NULL) {
        if (!addresses) {
            throw SocketException("addresses is null");
        }

        if (fd > 0) {
            close(fd);
            fd = -1;
        }

        ptr = ptr ? ptr : addresses;
        fd = ::socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (fd < 0) {
            throw SocketException("socket");
        }
    }

    void _setsockopt() {
        if (fd < 0) {
            throw SocketException("invalid fd");
        }

        int val = 1;
        if (::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val))) {
            throw SocketException("setsockopt");
        }
    }

    void _bind() {
        if (fd < 0) {
            throw SocketException("invalid fd");
        }

        if (!addresses) {
            throw SocketException("addresses is null");
        }

        if (::bind(fd, addresses->ai_addr, addresses->ai_addrlen)) {
            throw SocketException("bind");
        }
    }

    void _listen(int max_queued_waiters) {
        if (fd < 0) {
            throw SocketException("invalid fd");
        }

        if (::listen(fd, max_queued_waiters)) {
            throw SocketException("listen");
        }
    }

    int _accept() {
        if (fd < 0) {
            throw SocketException("invalid fd");
        }

        int peer = ::accept(fd, NULL, NULL);
        if (peer < 0) {
            throw SocketException("invalid peer skt");
        }

        return peer;
    }

    bool _connect(struct addrinfo* ptr) {
        if (fd < 0) {
            throw SocketException("invalid fd");
        }

        if (!addresses) {
            throw SocketException("addresses is null");
        }

        if (::connect(fd, ptr->ai_addr, ptr->ai_addrlen)) {
            return false;
        }

        return true;
    }

   public:
    Socket() : fd(-1), addresses(NULL) {}

    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    Socket(Socket&& movible) {
        this->fd = movible.fd;
        movible.fd = -1;
        this->addresses = movible.addresses;
        movible.addresses = NULL;
    }
    Socket& operator=(Socket&& movible) {
        this->fd = movible.fd;
        movible.fd = -1;
        this->addresses = movible.addresses;
        movible.addresses = NULL;
        return *this;
    }

    void listen(const char* port, int max_queued_waiters) {
        _getaddrinfo(NULL, port, true);
        _socket();
        _setsockopt();
        _bind();
        _listen(max_queued_waiters);
    }

    bool connect(const char* host, const char* service) {
        _getaddrinfo(host, service);

        struct addrinfo* ptr;
        bool connected = false;
        for (ptr = addresses; ptr != NULL && !connected; ptr = ptr->ai_next) {
            _socket(ptr);
            if (_connect(ptr)) {
                connected = true;
            }
        }

        return connected;
    }

    Socket accept() {
        return std::move(Socket(_accept()));
    }

    ssize_t recv(void* buf, size_t len, int flags) {
        if (fd < 0) {
            throw SocketException("invalid fd");
        }

        return ::recv(fd, buf, len, flags);
    }

    ssize_t send(const void* buf, size_t len, int flags) {
        if (fd < 0) {
            throw SocketException("invalid fd");
        }

        return ::send(fd, buf, len, flags);
    }

    size_t recv_all(char* buf, size_t len, int flags) {
        if (fd < 0) {
            throw SocketException("invalid fd");
        }

        ssize_t received = 0;
        ssize_t last_received = 0;
        while ((size_t)received < len) {
            last_received = ::recv(fd, &buf[received], len - received, flags);
            if (last_received < 0) {
                throw SocketException("recv");
            } else if (last_received == 0) {
                return received;
            } else {
                received += last_received;
            }
        }
        return (size_t)received;
    }

    size_t send_all(const char* buf, size_t len, int flags) {
        if (fd < 0) {
            throw SocketException("invalid fd");
        }

        ssize_t sent = 0;
        ssize_t last_sent = 0;
        while ((size_t)sent < len) {
            last_sent = ::send(fd, &buf[sent], len - sent, flags);
            if (last_sent < 0) {
                throw SocketException("send");
            } else if (last_sent == 0) {
                return sent;
            } else {
                sent += last_sent;
            }
        }
        return (size_t)sent;
    }

    ~Socket() {
        if (fd > 0) {
            shutdown(fd, SHUT_RDWR);
            close(fd);
            fd = -1;
        }

        if (addresses) {
            freeaddrinfo(addresses);
            addresses = NULL;
        }
    }
};

#endif  // __SOCKET_H__