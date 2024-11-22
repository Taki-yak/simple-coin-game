#ifndef BITMAPOBJECT_H
#define BITMAPOBJECT_H

#include "DrawableObject.h"
#include "TransformableObject.h"
#include <SDL.h>

class BitmapObject : public DrawableObject, public TransformableObject {
protected:
    SDL_Texture* texture;
    SDL_Renderer* renderer;

public:
    BitmapObject(SDL_Texture* tex, SDL_Renderer* rend)
        : texture(tex), renderer(rend) {}

    virtual ~BitmapObject();

    virtual void draw(int x, int y) override;
};

#endif 
