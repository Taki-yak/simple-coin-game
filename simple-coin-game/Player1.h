#ifndef PLAYER1_H
#define PLAYER1_H

#include "SpriteObject.h"
#include <unordered_map>
#include <string>
#include <vector>

class Player1 : public SpriteObject {
private:
    std::unordered_map<std::string, std::vector<SDL_Texture*>> directionSprites;
    std::string currentDirection;

public:
    Player1(const std::unordered_map<std::string, std::vector<SDL_Texture*>>& sprites, SDL_Renderer* rend);

    void setDirection(const std::string& direction);
    std::string getDirection() const;
    void animate() override;
};

#endif 
