/** Cola bloqueante implementación 2:
 * Utiliza una cola de PUNTEROS del objeto T alocado en el heap.
 * Cuando la misma se cierra permanentemente, se devuelve NULL.
 * 
 * NO toca la memoria en ningún momento. 
 * 
 * Al estar PROTEGIDA permite multi-threading, utiliza MUTEX.
 * 
 * (TODOS los métodos implementados toman el mutex para realizar las acciones
 * correspondientes, por lo que se omitirá esto en la documentación individual
 * de cada método para no ser redundantes).
*/

#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__

//-----------------------------------------------------------------------------
#include <queue>
#include <mutex>
#include <condition_variable>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#define QUEUE_CLOSED NULL;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

template <class T> class BlockingQueue {
    private:
        std::mutex m;
        std::queue<T*> queue;
        std::condition_variable cv;
        bool permanently_closed;

    public:
        /** 
         * Descripcion: constructor. Inicia el closed en false.
         * Parametros: -
        */
        BlockingQueue() : permanently_closed(false) {}


        /**
         * Deshabilitamos el constructor por copia y su operador.
         * NO podemos habilitar el constructor por movimiento, pues
         * los mutex son inamovibles.
        */
        BlockingQueue(const BlockingQueue&) = delete;
        BlockingQueue& operator=(const BlockingQueue&) = delete;


        /** 
         * Descripcion: inserta un objeto a la cola, y notifica a todos
         * los threads que esperan por la condition-variable.
         * Parametros: objeto de clase T.
         * Retorno: -
        */
        void push(T* t) {
            std::unique_lock<std::mutex> l(m);
            queue.push(t);
            cv.notify_all();
        }


        /** 
         * Descripcion: extrae un objeto de la cola. Si la misma está vacía,
         * pone a dormir al thread solicitante. Si la misma está vacía y
         * además cerrada, lanza excepción.
         * Parametros: -
         * Retorno: objeto de clase T.
        */
        T* pop() {
            std::unique_lock<std::mutex> l(m);
            while (queue.empty()) {
                if (permanently_closed) {
                    return QUEUE_CLOSED;
                }

                cv.wait(l);
            }

            T* t = queue.front();
            queue.pop();
            return t;
        }


        /** 
         * Descripcion: cierra la cola definitivamente, notificando a todos
         * los threads que esperan por la condition-variable.
         * Parametros: -
         * Retorno: -
        */
        void close() {
            std::unique_lock<std::mutex> l(m);
            permanently_closed = true;
            cv.notify_all();
        }


        /** 
         * Descripcion: destructor.
        */
        ~BlockingQueue() {}
};

//-----------------------------------------------------------------------------
#endif // __BLOCKING_QUEUE_H__
