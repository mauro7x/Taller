#ifndef __SOCKET_H__
#define __SOCKET_H__

//-----------------------------------------------------------------------------
#include <string>

// #include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/**
 * Socket. Descripcion. FALTA DOCUMENTAR.
*/
class Socket {
    private:
        int fd;
        bool fd_valid;

        /** (SERVER-SIDE)
         * Descripcion: obtiene la dirección donde se abrira el servidor a la
         * escucha de conexiones remotas.
         * Parametros: puerto, estructura de direccion.
         * Retorno: -
         * 
         * Se debe liberar la memoria reservada apuntada por address.
         * En caso de error se lanza una excepción (no es necesario
         * liberar address en este caso).
        */
        void _setServerAddress(const std::string& port, addrinfo** address);


        /** (CLIENT-SIDE)
         * Descripcion: obtiene las direcciones a las que se tratará de
         * conectar el servidor.
         * Parametros: hostname, puerto, estructura de direcciones.
         * Retorno: -
         * 
         * Se debe liberar la memoria reservada apuntada por addresses.
         * En caso de error se lanza una excepción (no es necesario
         * liberar addresses en este caso).
        */
        void _setClientAddresses(const std::string& hostname,
                                 const std::string& port,
                                 addrinfo** addresses);


        /** 
         * Descripcion: llama a la syscall socket() para obtener el fd.
         * Parametros: estructura de direccion para crear el socket,
         * estructura de direcciones a liberar en caso de error.
         * Retorno: -
         * 
         * En caso de error libera la memoria de all_addresses y se lanza
         * una excepción.
        */
        void _setFd(addrinfo* address, addrinfo* all_addresses);

        
        /** (SERVER-SIDE)
         * Descripcion: arregla el problema de TIMEWAIT de existir.
         * Parametros: estructura de dirección.
         * Retorno: -
         * 
         * En caso de error libera la memoria de address y se lanza una
         * excepción.
        */
        void _fixTimeWait(addrinfo* address);


        /** (SERVER-SIDE)
         * Descripcion: realiza el bind del socket a address.
         * Parametros: estructura de dirección a la que bindear el socket.
         * Retorno: -
         * 
         * Libera la memoria de address.
         * En caso de error se lanza una excepción.
        */
        void _bind(addrinfo* address);


        /** (SERVER-SIDE)
         * Descripcion: pone a la escucha al servidor. Se establece
         * @max_queued_clients como limite a la cantidad de clientes encolados
         * esperando ser aceptados.
         * Parametros: cantidad límite de clientes encolados.
         * Retorno: -
         * 
         * En caso de error se lanza una excepción.
        */
        void _listen(const int& max_queued_clients);


        /** (CLIENT-SIDE)
         * Descripcion: intenta conectarse a todas las direcciones en la 
         * estructura de direcciones recibida. Si no lo logra, lanza excepción.
         * Parametros: estructura de direcciones.
         * Retorno: -
         * 
         * Libera la memoria de addresses.
         * En caso de error se lanza una excepción.
        */
        void _tryToConnectTo(addrinfo* addresses);


        /** 
         * Descripcion: si el fd es valido, lo cierra.
         * Parametros: -
         * Retorno: -
        */
        void _closeFdIfValid();

        
    public:
        /** (SERVER-SIDE)
         * Diseñado para ser utilizado por el SERVIDOR para ponerse a la
         * escucha de conexiones entrantes.
         * 
         * Descripcion: constructor con un puerto y la cantidad de clientes
         * que pueden haber simultaneamente esperando a ser aceptados.
         * Parametros: puerto , máxima cantidad de clientes encolados.
         * 
         * En caso de error se lanza una excepción.
        */
        Socket(const std::string& port, const int& max_queued_clients);


        /** (SERVER-SIDE)
         * Diseñado para ser utilizado por el SERVIDOR para crear los
         * socket peer con los que se comunica con sus clientes.
         * 
         * Descripcion: constructor con fd.
         * Parametros: file descriptor.
         * 
         * Se toma la responsabilidad del cierre del fd.
        */
        Socket(const int& fd);

        
        /** (CLIENT-SIDE)
         * Diseñado para ser utilizado por el CLIENTE para conectarse
         * a un determinado servidor.
         * 
         * Descripcion: constructor con hostname y puerto.
         * Parametros: nombre del host y puerto al que conectarse.
         * 
         * En caso de error se lanza una excepción.
        */
        Socket(const std::string& hostname, const std::string& port);


        /** 
         * Deshabilitamos el constructor por copia y su operador.
        */
        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;


        /** 
         * Habilitamos el constructor por movimiento y su operador.
        */
        Socket(Socket&& other);
        Socket& operator=(Socket&& other);


        /** (SERVER-SIDE)
         * Descripcion: acepta la conexión de un cliente.
         * Parametros: -
         * Retorno: file descriptor del socket aceptado. En caso de error,
         * se lanza una excepción.
         * 
         * No toma la responsabilidad de cerrar el fd devuelto.
        */
        int accept();


        /** 
         * Descripcion: 
         * Parametros: -
         * Retorno: N, si n>0: cantidad de bytes enviados.
         *             si n==0: el socket fue cerrado.
         * 
         * En caso de error se lanza una excepción.
        */
        ssize_t send(const char* source, const ssize_t& len);


        /**
         * Descripción: sobrecarga de operador << para distintos
         * tipos de datos a enviar.
         * 
         * COMPLETAR DOCUMENTACIÓN
        */
        ssize_t operator<<(std::string& msg);


        /** 
         * Descripcion: 
         * Parametros: -
         * Retorno: N, si n>0: cantidad de bytes recibidos.
         *             si n==0: el socket fue cerrado.
         * 
         * En caso de error se lanza una excepción.
        */
        ssize_t recv(char* buffer, const ssize_t& len);


        /**
         * Descripción: sobrecarga de operador >> para distintos
         * tipos de datos a recibir.
         * 
         * COMPLETAR DOCUMENTACIÓN
        */
        ssize_t operator>>(std::string& msg);


        /** 
         * Descripcion: cierra un canal del socket.
         * Parametros: canal a cerrar, si no se recibe, por defecto se cierran
         * ambos canales (lectura y escritura).
         * Retorno: -
        */
        void shutdown(const int& channel=SHUT_RDWR);


        /** 
         * Descripcion: destructor.
         * Cierra el file descriptor asociado al socket.
        */
        ~Socket();
};

//-----------------------------------------------------------------------------
#endif // __SOCKET_H__
