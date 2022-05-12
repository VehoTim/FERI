#include "Game.h"

using namespace std;

int main() {
    Game game;
    game.addPlayer(0, 0, 10, 20, "Brane");
    game.addPlayer(50, 0, 10, 20, "S1mple");
    game.addPlayer(150, 0, 10, 20, "Johnny");

    game.render();
    game.pause();
    game.update();
    game.render();
    game.play();
    game.update();
    game.render();
    game.gameOver();
    game.update();
    game.render();

    return 0;
}