#include "BitmapHandler.h"

SDL_Texture* BitmapHandler::loadFromFile(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture) {
        std::cerr << "Unable to load texture " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    return texture;
}

void BitmapHandler::destroyBitmap(SDL_Texture* texture) {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}
