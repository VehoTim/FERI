#ifndef NALOGA0601_GAME_H
#define NALOGA0601_GAME_H

#include "GameState.h"
#include "GameObject.h"
#include "Player.h"
#include <vector>
#include <string>

class Game {
private:
    GameState state;
    std::vector<GameObject*> gameObjects;
public:
    Game();
    void addPlayer(float x, float y, float width, float height, const std::string &name);
    void render();
    void update();
    void play();
    void pause();
    void gameOver();
};


#endif //NALOGA0601_GAME_H
