#include <iostream>
#include "Game.h"


int main() {
    Game game;
    do {
        game.startNewGame();
        game.playerTurn();
        game.dealerTurn();
        game.decideOutcome();
    } while (game.playAgain());

    std::cout << "Game Over" << std::endl;
    return 0;
}
