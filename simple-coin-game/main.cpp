#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "BitmapHandler.h"
#include "Player1.h"
#include "LineSegment.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>  
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool checkCollision(int playerX, int playerY, int coinX, int coinY, int size = 32) {
    return (playerX < coinX + size && playerX + size > coinX &&
        playerY < coinY + size && playerY + size > coinY);
}

int main(int argc, char* args[]) {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

        SDL_Window* window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!window || !renderer) {
        std::cerr << "Failed to create window or renderer!" << std::endl;
        Mix_CloseAudio();
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    BitmapHandler bitmapHandler;

        std::unordered_map<std::string, std::vector<SDL_Texture*>> playerSprites;
    playerSprites["right"] = { bitmapHandler.loadFromFile("images/right1.png", renderer), bitmapHandler.loadFromFile("images/right2.png", renderer) };
    playerSprites["left"] = { bitmapHandler.loadFromFile("images/left1.png", renderer), bitmapHandler.loadFromFile("images/left2.png", renderer) };
    playerSprites["down"] = { bitmapHandler.loadFromFile("images/down1.png", renderer), bitmapHandler.loadFromFile("images/down2.png", renderer) };
    playerSprites["up"] = { bitmapHandler.loadFromFile("images/up1.png", renderer), bitmapHandler.loadFromFile("images/up2.png", renderer) };

        SDL_Texture* coinTexture = bitmapHandler.loadFromFile("images/coin.png", renderer);
    if (!coinTexture) {
        std::cerr << "Failed to load coin image! Make sure 'images/coin.png' exists." << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

        Mix_Chunk* moveSound = Mix_LoadWAV("audio/step.wav");
    if (!moveSound) {
        std::cerr << "Failed to load move sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }

    Mix_Chunk* coinSound = Mix_LoadWAV("audio/coin.wav");
    if (!coinSound) {
        std::cerr << "Failed to load coin pickup sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }

        Player1 player1(playerSprites, renderer);
    player1.setDirection("down");
    int playerX = 100, playerY = 100;

        const int NUM_COINS = 5;
    std::vector<std::pair<int, int>> coinPositions;
    for (int i = 0; i < NUM_COINS; ++i) {
        int x = rand() % (SCREEN_WIDTH - 32);
        int y = rand() % (SCREEN_HEIGHT - 32);
        coinPositions.emplace_back(x, y);
    }

        LineSegment boundaryLine;
    bool drawingStart = true;

        bool quit = false;
    SDL_Event e;
    int score = 0;
    int speed = 7; 
        bool hasMoved = false; 
    while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    if (drawingStart) {
                        boundaryLine.setStart(e.button.x, e.button.y);
                        drawingStart = false;
                    }
                    else {
                        boundaryLine.setEnd(e.button.x, e.button.y);
                        drawingStart = true;
                    }
                }
            }
            else if (e.type == SDL_KEYDOWN) {
                bool moved = false;
                switch (e.key.keysym.sym) {
                case SDLK_RIGHT:
                    player1.setDirection("right");
                    playerX += speed;
                    moved = true;
                    break;
                case SDLK_LEFT:
                    player1.setDirection("left");
                    playerX -= speed;
                    moved = true;
                    break;
                case SDLK_DOWN:
                    player1.setDirection("down");
                    playerY += speed;
                    moved = true;
                    break;
                case SDLK_UP:
                    player1.setDirection("up");
                    playerY -= speed;
                    moved = true;
                    break;
                }

                                if (moved && !hasMoved && moveSound) {
                    Mix_PlayChannel(-1, moveSound, 0);                      hasMoved = true;                  }
            }
        }

                if (boundaryLine.isDefined() && boundaryLine.isPointBelow(playerX, playerY)) {
            playerX = 100;
            playerY = 100;
        }

                for (size_t i = 0; i < coinPositions.size(); ++i) {
            if (checkCollision(playerX, playerY, coinPositions[i].first, coinPositions[i].second)) {
                coinPositions.erase(coinPositions.begin() + i);
                score += 10;

                                if (coinSound) {
                    Mix_PlayChannel(-1, coinSound, 0);                  }

                break;
            }
        }

                if (coinPositions.empty()) {
            std::cout << "You collected all coins! Final Score: " << score << std::endl;
            quit = true;
        }

                SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
        SDL_RenderClear(renderer);

                boundaryLine.draw(renderer);

                player1.animate();
        player1.draw(playerX, playerY);

                for (const auto& pos : coinPositions) {
            SDL_Rect coinRect = { pos.first, pos.second, 32, 32 };
            SDL_RenderCopy(renderer, coinTexture, nullptr, &coinRect);
        }

                SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

        bitmapHandler.destroyBitmap(coinTexture);
    for (const auto& sprites : playerSprites) {
        for (auto* texture : sprites.second) {
            bitmapHandler.destroyBitmap(texture);
        }
    }

    Mix_FreeChunk(moveSound);
    Mix_FreeChunk(coinSound);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
