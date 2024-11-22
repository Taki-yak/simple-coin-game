#pragma once
#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include "Point2D.h"
#include <SDL.h>

class LineSegment {
private:
    Point2D start;
    Point2D end;
    bool defined;  
public:
    LineSegment() : defined(false) {}

    void setStart(int x, int y) {
        start.set(x, y);
        defined = false;  
    }

    void setEnd(int x, int y) {
        end.set(x, y);
        defined = true;  
    }

    bool isDefined() const {
        return defined;
    }

    void draw(SDL_Renderer* renderer) const {
        if (defined) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  
            SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
        }
    }

    bool isPointBelow(int x, int y) const {
        if (!defined) return false; 

       
        return y > start.y && y > end.y;
    }
};

#endif
