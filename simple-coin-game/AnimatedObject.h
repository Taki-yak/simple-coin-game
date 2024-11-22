#include <SDL.h>
#include <SDL_image.h>
#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

class AnimatedObject {
public:
    virtual void animate() = 0;
};

#endif 

