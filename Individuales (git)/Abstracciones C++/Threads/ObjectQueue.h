#ifndef __OBJECT_QUEUE_H__
#define __OBJECT_QUEUE_H__

//-----------------------------------------------------------------------------
#include <queue>
#include <mutex>
#include <condition_variable>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
typedef int Object; // reemplazar por el objeto correcto
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/**
 * Cola bloqueante de Objetos (definidos, implementada desde la alternativa 1).
 * Al estar PROTEGIDA permite multi-threading, utiliza MUTEX.
 * 
 * (TODOS los métodos implementados toman el mutex para realizar las acciones
 * correspondientes, por lo que se omitirá esto en la documentación individual
 * de cada método para no ser redundantes).
*/
class ObjectQueue {
    private:
        std::mutex m;
        std::queue<Object> queue;
        std::condition_variable cv;
        bool permanently_closed;

    public:
        /** 
         * Descripcion: constructor. Inicia el closed en false.
         * Parametros: -
        */
        ObjectQueue();


        /**
         * Deshabilitamos el constructor por copia y su operador.
         * NO podemos habilitar el constructor por movimiento, pues
         * los mutex son inamovibles.
        */
        ObjectQueue(const ObjectQueue&) = delete;
        ObjectQueue& operator=(const ObjectQueue&) = delete;
        

        /** 
         * Descripcion: inserta un objeto a la cola, y notifica a todos
         * los threads que esperan por la condition-variable.
         * Parametros: objeto de clase T.
         * Retorno: -
        */
        void push(Object object);


        /** 
         * Descripcion: extrae un objeto de la cola. Si la misma está vacía,
         * pone a dormir al thread solicitante. Si la misma está vacía y
         * además cerrada, lanza excepción.
         * Parametros: -
         * Retorno: objeto de clase T.
        */
        Object pop();


        /** 
         * Descripcion: cierra la cola definitivamente, notificando a todos
         * los threads que esperan por la condition-variable.
         * Parametros: -
         * Retorno: -
        */
        void close();


        /** 
         * Descripcion: destructor.
        */
        ~ObjectQueue();
};

//-----------------------------------------------------------------------------
#endif // __OBJECT_QUEUE_H__
