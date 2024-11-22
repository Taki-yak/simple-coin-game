#ifndef BITMAPHANDLER_H
#define BITMAPHANDLER_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class BitmapHandler {
public:
    SDL_Texture* loadFromFile(const std::string& path, SDL_Renderer* renderer);
    void destroyBitmap(SDL_Texture* texture);
};

#endif 
