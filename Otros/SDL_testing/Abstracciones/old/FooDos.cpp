#include "FooDos.h"

//-----------------------------------------------------------------------------
// Métodos privados
#include <iostream>

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// API Pública

FooDos::FooDos(SDL_Renderer* renderer, int pPosX, int pPosY)
    : Entity(renderer),
      mPosX(pPosX),
      mPosY(pPosY),
      current_animation(NULL),
      current_frame(0),
      flipType(SDL_FLIP_NONE) {
    mIdleSprites.reserve(FOODOS_IDLE_SPRITES);
    for (int i = 0; i < FOODOS_IDLE_SPRITES; i++) {
        mIdleSprites.push_back(Texture(renderer));
    }
    mIdleSprites.shrink_to_fit();

    mWalkSprites.reserve(FOODOS_WALK_SPRITES);
    for (int i = 0; i < FOODOS_WALK_SPRITES; i++) {
        mWalkSprites.push_back(Texture(renderer));
    }
    mWalkSprites.shrink_to_fit();
}

void FooDos::loadMedia() {
    std::string filepath;
    for (int i = 0; i < FOODOS_IDLE_SPRITES; i++) {
        filepath =
            "../assets/zombiefiles/Idle (" + std::to_string(i + 1) + ").png";
        mIdleSprites[i].loadFromFile(filepath);
    }

    for (int i = 0; i < FOODOS_WALK_SPRITES; i++) {
        filepath =
            "../assets/zombiefiles/Walk (" + std::to_string(i + 1) + ").png";
        mWalkSprites[i].loadFromFile(filepath);
    }
}

void FooDos::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_a:
                flipType = SDL_FLIP_HORIZONTAL;
                break;

            case SDLK_d:
                flipType = SDL_FLIP_NONE;
                break;
        }
    }
}

void FooDos::act() {
    if (current_frame == mIdleSprites.end()) {
        current_frame = mIdleSprites.begin();
    } else {
        current_frame++;
        if (current_frame == mIdleSprites.end()) {
            current_frame = mIdleSprites.begin();
        }
    }
}

void FooDos::render() const {
    (*current_frame).render(mPosX, mPosY, NULL, 0.0, NULL, flipType);
}

void FooDos::free() {}

FooDos::~FooDos() {}

//-----------------------------------------------------------------------------
