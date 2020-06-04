#include "Foo.h"

//-----------------------------------------------------------------------------
// Métodos privados

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// API Pública

Foo::Foo(SDL_Renderer* renderer)
    : Entity(renderer),
      mCurrentClip(NULL),
      mSpriteSheetTexture(renderer),
      current_frame(0) {}

void Foo::loadMedia() {
    mSpriteSheetTexture.loadFromFile("../assets/foo.png", 0, 0xFF, 0xFF);

    // Set sprite clips
    mSpriteClips[0].x = 0;
    mSpriteClips[0].y = 0;
    mSpriteClips[0].w = 64;
    mSpriteClips[0].h = 205;

    mSpriteClips[1].x = 64;
    mSpriteClips[1].y = 0;
    mSpriteClips[1].w = 64;
    mSpriteClips[1].h = 205;

    mSpriteClips[2].x = 128;
    mSpriteClips[2].y = 0;
    mSpriteClips[2].w = 64;
    mSpriteClips[2].h = 205;

    mSpriteClips[3].x = 196;
    mSpriteClips[3].y = 0;
    mSpriteClips[3].w = 64;
    mSpriteClips[3].h = 205;

    mCurrentClip = &mSpriteClips[0];
}

void Foo::handleEvent(const SDL_Event& e) {}

void Foo::act() {
    // Go to next frame
    ++current_frame;

    // Cycle animation
    if (current_frame / 4 >= WALKING_ANIMATION_FRAMES) {
        current_frame = 0;
    }

    mCurrentClip = &mSpriteClips[current_frame / 4];
}

void Foo::render() const {
    mSpriteSheetTexture.render((WINDOW_WIDTH - mCurrentClip->w) / 2,
                               (WINDOW_HEIGHT - mCurrentClip->h) / 2,
                               mCurrentClip);
}

void Foo::free() {
    mSpriteSheetTexture.free();
}

Foo::~Foo() {
    free();
}

//-----------------------------------------------------------------------------
