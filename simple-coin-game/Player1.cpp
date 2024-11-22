#include "Player1.h"

Player1::Player1(const std::unordered_map<std::string, std::vector<SDL_Texture*>>& sprites, SDL_Renderer* rend)
    : SpriteObject(rend, sprites.at("down")), directionSprites(sprites), currentDirection("down") {}

void Player1::setDirection(const std::string& direction) {
    if (directionSprites.count(direction)) {
        currentDirection = direction;
        frames = directionSprites[direction];
        currentFrame = 0;
        texture = frames[currentFrame];
    }
}

std::string Player1::getDirection() const {
    return currentDirection;
}

void Player1::animate() {
    SpriteObject::animate();
}
