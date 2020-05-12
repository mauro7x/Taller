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
#define SHUTDOWN_SKT_ERROR 8

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/**
 * Extensión de std::exception para agregar códigos de error personalizados.
*/
class Exception : virtual public std::exception {
    private:
        int error_code;
        std::string error_msg;

    public:
        /** 
         * Descripcion: constructor.
         * Parametros: codigo de error, mensaje de error.
        */
        explicit Exception(const int error_code, const std::string error_msg);


        /** 
         * Descripcion: devuelve el código de error.
         * Parametros: -
         * Retorno: código de error.
        */
        int getErrorCode() const throw();


        /** 
         * Descripcion: devuelve el mensaje de error.
         * Parametros: -
         * Retorno: mensaje de error.
         * 
         * ACLARACION: no hay que ocuparse del puntero recibido.
        */
        const char* what() const throw();
        
        
        /** 
         * Descripcion: destructor.
        */
        ~Exception() throw();
};

//-----------------------------------------------------------------------------
#endif // __EXCEPTION_H__
