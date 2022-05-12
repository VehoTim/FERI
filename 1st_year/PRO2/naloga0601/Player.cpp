#include "Player.h"
#include <iostream>

Player::Player(float x, float y, float height, float width, const std::string &name) : GameObject(x, y, height, width),
                                                                                 name(name) {};


void Player::draw() {
    std::cout << "x: " << x << "y: " << y << ", height: " << height << ", width: " << width << ", name: " << name;
}

void Player::update() { x++; }