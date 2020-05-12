#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

//-----------------------------------------------------------------------------
#include <exception>
#include <string>
//-----------------------------------------------------------------------------
// Códigos de error:
// #define ERROR_EJEMPLO 1
// ...
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
