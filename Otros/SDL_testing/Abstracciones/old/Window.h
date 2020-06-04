#ifndef __WINDOW_H__
#define __WINDOW_H__

//-----------------------------------------------------------------------------
#include <SDL2/SDL.h>

#include "SDLException.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// DEFINES
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/* Wrapper para SDL_Window. */
class Window {
   private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    // Dimensiones
    int mWidth;
    int mHeight;

    // Posición inicial
    int mInitialPosX;
    int mInitialPosY;

    // Config
    bool vsync;

   public:
    /**
     * Descripción: constructor.
     *
     * Parámetros: -
     */
    Window(int pWidth, int pHeight, int pInitialPosX = SDL_WINDOWPOS_UNDEFINED,
           int pInitialPosY = SDL_WINDOWPOS_UNDEFINED, bool vsync = true);

    /* Deshabilitamos el constructor por copia. */
    Window(const Window&) = delete;

    /* Deshabilitamos el operador= para copia.*/
    Window& operator=(const Window&) = delete;

    /* Deshabilitamos el constructor por movimiento. */
    Window(Window&& other) = delete;

    /* Deshabilitamos el operador= para movimiento. */
    Window& operator=(Window&& other) = delete;

    /**
     * Descripción: inicializa recursos.
     *
     * Parámetros: -
     *
     * Retorno: -
     *
     */
    void init();

    /**
     * Descripción: limpia la pantalla de color blanco.
     *
     * Parámetros: -
     *
     * Retorno: -
     *
     */
    void clear() const;

    /**
     * Descripción: presenta la pantalla renderizada.
     *
     * Parámetros: -
     *
     * Retorno: -
     *
     */
    void present() const;

    /**
     * Descripción: inicializa recursos.
     *
     * Parámetros: -
     *
     * Retorno: -
     *
     */
    void free();

    /**
     * Descripción: destructor.
     */
    ~Window();
};

//-----------------------------------------------------------------------------

#endif  // __WINDOW_H__
