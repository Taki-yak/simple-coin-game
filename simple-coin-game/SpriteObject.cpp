#include "SpriteObject.h"

void SpriteObject::animate() {
    frameCounter++;
    if (frameCounter >= frameDelay) {
        currentFrame = (currentFrame + 1) % frames.size();
        texture = frames[currentFrame];
        frameCounter = 0;
    }
}

void SpriteObject::draw(int x, int y) {
    BitmapObject::draw(x, y);
}
