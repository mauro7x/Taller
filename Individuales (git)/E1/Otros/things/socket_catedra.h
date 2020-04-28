// socket catedra, funciones que deberia implementar...

#include <sys/types.h>
#include <sys/socket.h>

typedef struct socket_t {
    int socket;
} socket_t;

int socket_create(socket_t* self);

int socket_destroy(socket_t* self);

/**
 * Asigna una direccion al socket y lo marca como socket pasivo.
 * (lado del servidor)
 */
int socket_bind_and_listen(socket_t *self, const char* service);

/**
 * Espera a que se conecte un cliente y lo asigna en accepted_socket.
 * (lado del servidor)
 * 0 si ok, -1 si hay error
 */
int socket_accept(socket_t* self, socket_t* accepted_socket);

/**
 * Se conecta a un servior dada una direccion y un servicio o puerto,
 * (lado del cliente)
 * 0 si ok, -1 si hay error
 */
int socket_connect(socket_t* self);

/**
 * Intenta enviar @param_length bytes a traves del socket.
 * @return cantidad de bytes enviados o -1 si hay error.
 */
int socket_send(socket_t* self);

/**
 * Intenta recibir @param_length bytes a traves del socket.
 * @return cantidad de bytes recibidos o -1 si hay error.
 */
int socket_receive(socket_t* self);

/**
 * Cierra los canales de lectura y escritura.
 * 0 si ok, -1 si hay error
 */
void socket_shutdown(socket_t* self);



