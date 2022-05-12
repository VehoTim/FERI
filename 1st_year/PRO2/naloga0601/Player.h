#ifndef NALOGA0601_PLAYER_H
#define NALOGA0601_PLAYER_H

#include "GameObject.h"
#include <string>

class Player : public GameObject {
private:
    std::string name;
public:
    Player(float x, float y, float height, float width, const std::string &name);
    void draw() override;
    void update() override;
};


#endif //NALOGA0601_PLAYER_H
