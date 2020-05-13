#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

//-----------------------------------------------------------------------------
#include <exception>
#include <string>
//-----------------------------------------------------------------------------
// Códigos de error:
#define GET_ADDRESS_SKT_ERROR 1
#define SET_FD_SKT_ERROR 2
#define FIX_TW_SKT_ERROR 3
#define BIND_SKT_ERROR 4
#define LISTEN_SKT_ERROR 5
#define ACCEPT_SKT_ERROR 6
#define CONNECT_SKT_ERROR 7
#define SENT_SKT_ERROR 8
#define RECV_SKT_ERROR 9
#define SHUTDOWN_SKT_ERROR 10

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/**
 * Extensión de std::exception para agregar un código de error particular.
*/
class Exception : public std::exception {
    private:
        int error_code;
        std::string error_msg;

    public:
        /** 
         * Descripcion: constructor.
         * Parametros: codigo de error, mensaje de error.
        */
        Exception(const int error_code, const std::string error_msg);


        /** 
         * Descripcion: devuelve el código de error.
         * Parametros: -
         * Retorno: código de error.
        */
        int getErrorCode();


        /** 
         * Descripcion: devuelve el mensaje de error.
         * Parametros: -
         * Retorno: mensaje de error.
         * 
         * No hay que ocuparse del puntero recibido.
        */
        const char* what();


        /** 
         * Descripcion: destructor.
        */
        ~Exception();
};

//-----------------------------------------------------------------------------
#endif // __EXCEPTION_H__
