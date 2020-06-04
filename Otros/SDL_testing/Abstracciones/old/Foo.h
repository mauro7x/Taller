#ifndef __FOO_H__
#define __FOO_H__

//-----------------------------------------------------------------------------
#include "Entity.h"
#include "Texture.h"
#include "config.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#define WALKING_ANIMATION_FRAMES 4
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Foo : public Entity {
   private:
    SDL_Rect mSpriteClips[WALKING_ANIMATION_FRAMES];
    SDL_Rect* mCurrentClip;
    Texture mSpriteSheetTexture;
    int current_frame;

   public:
    /* Constructor */
    Foo(SDL_Renderer* renderer);

    //-------------------------------------------------------------------------
    // Interfaz genérica de Entidad

    /* Inicializar la media necesaria */
    void loadMedia() override;

    /* Manejar evento del usuario */
    void handleEvent(const SDL_Event& e) override;

    /* Acción en cada frame */
    void act() override;

    /* Renderizarse */
    void render() const override;

    /* Liberar sus recursos (SI ES NECESARIO) */
    void free() override;

    //-------------------------------------------------------------------------

    /* Destructor */
    ~Foo();
};

//-----------------------------------------------------------------------------

#endif  // __FOO_H__
