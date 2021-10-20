#include "Game.h"
#include <iostream>

Game::Game() : state(GameState::PLAY) {}

void Game::addPlayer(float x, float y, float width, float height, const std::string &name) {
    Player* tmp = new Player(x, y, height, width, name);
    gameObjects.push_back(tmp);
}

void Game::render() {
    for(GameObject* go : gameObjects){
        go->draw();
        std::cout << std::endl;
    }
    if (state == GameState::GAME_OVER) std::cout << "GAME OVER";
    else if(state == GameState::PAUSE) std::cout << "PAUSE";

    std::cout << std::endl;
}

void Game::update() {
    if (state == GameState::PLAY){
        for(GameObject* go : gameObjects){
            go->update();
        }
    }
}

void Game::play() { state = GameState::PLAY; }

void Game::pause() { state = GameState::PAUSE; }

void Game::gameOver() { state = GameState::GAME_OVER; }



