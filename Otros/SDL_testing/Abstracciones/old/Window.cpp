#include "Window.h"

//-----------------------------------------------------------------------------
// Métodos privados

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// API Pública

Window::Window(int pWidth, int pHeight, int pInitialPosX, int pInitialPosY,
               bool vsync)
    : mWindow(NULL),
      mRenderer(NULL),
      mWidth(pWidth),
      mHeight(pHeight),
      mInitialPosX(pInitialPosX),
      mInitialPosY(pInitialPosY),
      vsync(vsync) {}

void Window::init() {
    mWindow = SDL_CreateWindow("SDL Tutorial", mInitialPosX, mInitialPosY,
                               mWidth, mHeight, SDL_WINDOW_SHOWN);
    if (mWindow == NULL) {
        throw SDLException("Error in window init: SDL_CreateWindow()",
                           SDL_GetError());
    }

    Uint32 renderer_flags =
        vsync ? (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
              : (SDL_RENDERER_ACCELERATED);

    mRenderer = SDL_CreateRenderer(mWindow, -1, renderer_flags);
    if (mRenderer == NULL) {
        throw SDLException("Error in window init: SDL_CreateRenderer()",
                           SDL_GetError());
    }

    // Initialize renderer color
    if (SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF)) {
        throw SDLException("Error in window init: SDL_SetRenderDrawColor()",
                           SDL_GetError());
    }
}

void Window::clear() const {
    if (SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF)) {
        throw SDLException("Error in window clear: SDL_SetRenderDrawColor()",
                           SDL_GetError());
    }

    if (SDL_RenderClear(mRenderer)) {
        throw SDLException("Error in window clear: SDL_RenderClear()",
                           SDL_GetError());
    }
}

void Window::present() const {
    SDL_RenderPresent(mRenderer);
}

void Window::free() {
    if (mWindow) {
        SDL_DestroyWindow(mWindow);
        mWindow = NULL;
    }

    if (mRenderer) {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = NULL;
    }
}

Window::~Window() {
    free();
}

//-----------------------------------------------------------------------------
