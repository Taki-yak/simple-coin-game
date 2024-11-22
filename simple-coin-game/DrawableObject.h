class DrawableObject {
public:
    virtual void animate() {}; 
    virtual void draw(int x, int y) = 0;
    virtual ~DrawableObject() = default;
};
