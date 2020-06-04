#ifndef __FOO_DOS_H__
#define __FOO_DOS_H__

//-----------------------------------------------------------------------------
#include <vector>

#include "Entity.h"
#include "Texture.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#define FOODOS_IDLE_SPRITES 15
#define FOODOS_WALK_SPRITES 10
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class FooDos : public Entity {
   private:
    const int mWidth = 614;
    const int mHeight = 564;
    int mPosX;
    int mPosY;
    std::vector<Texture> mIdleSprites;
    std::vector<Texture> mWalkSprites;

    std::vector<Texture>* current_animation;
    int current_frame;
    SDL_RendererFlip flipType;

   public:
    /* Constructor */
    FooDos(SDL_Renderer* renderer, int pPosX, int pPosY);

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
    ~FooDos();
};

//-----------------------------------------------------------------------------

#endif  // __FOO_DOS_H__
