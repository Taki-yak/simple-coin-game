#pragma once
#ifndef POINT2D_H
#define POINT2D_H

class Point2D {
public:
    int x, y;

    Point2D() : x(0), y(0) {}
    Point2D(int x, int y) : x(x), y(y) {}

    void set(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

#endif 
