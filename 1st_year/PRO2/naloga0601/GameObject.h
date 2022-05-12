#ifndef NALOGA0601_GAMEOBJECT_H
#define NALOGA0601_GAMEOBJECT_H


class GameObject {
protected:
    float x;
    float y;
    float width;
    float height;
public:
    GameObject(float x, float y, float width, float height);
    virtual ~GameObject() = default;
    virtual void draw() = 0;
    virtual void update() = 0;
};


#endif //NALOGA0601_GAMEOBJECT_H
