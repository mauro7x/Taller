#ifndef __ACTIVE_OBJECT_H__
#define __ACTIVE_OBJECT_H__

//-----------------------------------------------------------------------------
#include "Thread.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/**
 * Objecto activo.
 * Corre en su propio hilo de ejecución, pues hereda de Thread.
*/
class ActiveObject : public Thread {
    private:
        // Atributos del objeto activo.

    public:
        /** 
         * Descripcion: constuctor.
         * Parametros: -
        */
        ActiveObject();


        /** 
         * Descripcion: código que se ejecutará al correr el hilo.
         * Parametros: -
         * Retorno: -
        */
        virtual void run() override;


        /** 
         * Descripcion: destructor.
        */
        virtual ~ActiveObject();
};

//-----------------------------------------------------------------------------
#endif // __ACTIVE_OBJECT_H__
