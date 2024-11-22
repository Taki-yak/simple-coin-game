#ifndef TRANSFORMABLEOBJECT_H
#define TRANSFORMABLEOBJECT_H

class TransformableObject {
protected:
    int posX;
    int posY;

public:
    TransformableObject() : posX(0), posY(0) {}

    void setPosition(int x, int y) { posX = x; posY = y; }
    int getX() const { return posX; }
    int getY() const { return posY; }
};

#endif 