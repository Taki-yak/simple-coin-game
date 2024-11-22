#include "BitmapObject.h"

BitmapObject::~BitmapObject() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void BitmapObject::draw(int x, int y) {
    if (texture) {
        SDL_Rect renderQuad = { x, y, 0, 0 };
        SDL_QueryTexture(texture, nullptr, nullptr, &renderQuad.w, &renderQuad.h);
        SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);
    }
}
