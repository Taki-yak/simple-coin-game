#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include "BitmapObject.h"
#include <vector>

class SpriteObject : public BitmapObject {
protected:
    std::vector<SDL_Texture*> frames;
    int currentFrame;
    int frameDelay;
    int frameCounter;

public:
    SpriteObject(SDL_Renderer* rend, const std::vector<SDL_Texture*>& textures, int delay = 10)
        : BitmapObject(nullptr, rend), frames(textures), currentFrame(0), frameDelay(delay), frameCounter(0) {}

    void animate();
    virtual void draw(int x, int y) override;
};

#endif 
