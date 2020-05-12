#ifndef __PROTECTED_OBJECT_H__
#define __PROTECTED_OBJECT_H__

//-----------------------------------------------------------------------------
#include <mutex>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/**
 * Objeto protegido (permite multi-threading utilizando MUTEX).
 * 
 * (TODOS los métodos implementados toman el mutex para realizar las acciones
 * correspondientes, por lo que se omitirá esto en la documentación individual
 * de cada método para no ser redundantes).
*/
class ProtectedObject {
    private:
        std::mutex m;
        // Object object;

    public:
        /** 
         * Descripcion: constructor.
         * Parametros: -
        */
        ProtectedObject();


        /** 
         * Deshabilitamos el constructor por copia y su operador.
         * NO podemos habilitar el constructor por movimiento, pues
         * los mutex son inamovibles.
        */
        ProtectedObject(const ProtectedObject&) = delete;
        ProtectedObject& operator=(const ProtectedObject&) = delete;


        /** 
         * Descripcion: TODOS los métodos de la API pública deberían ser
         * critical sections para nuestro programa.
         * Parametros: -
         * Retorno: -
        */
        void criticalSectionMethod();


        /** 
         * Descripcion: destructor.
        */
        ~ProtectedObject();
};

//-----------------------------------------------------------------------------
#endif // __PROTECTED_OBJECT_H__
