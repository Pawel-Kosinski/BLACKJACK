#include <iostream>
#include "Game.h"


int main() {
    Game game;
    do {
        game.startNewGame();
        int check = game.playerTurn();
        if (check != 1) {
            game.dealerTurn();
            game.decideOutcome();
        }
    } while (game.getAllCoins() != 0 && game.playAgain());
    if (game.getAllCoins() == 0)
        std::cout << "You have 0 coins" << std::endl;
    std::cout << "Game Over" << std::endl;
    return 0;
}
