#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "Game.h"
#include "Renderer.h"

int main() {
    Renderer renderer;
    Game game;

    while (renderer.isRunning()) {
        renderer.pollEvents();
        renderer.update();

        if (renderer.getGameState() == Renderer::gameLoop) {

            while (renderer.isRunning() && renderer.getGameState() == Renderer::gameLoop) {
                game.startNewGame(*renderer.getWindow(), renderer);
                renderer.pollEvents();
                renderer.update();

                game.displayPlayerHand(*renderer.getWindow());
                renderer.render();

                if (game.playerTurn(*renderer.getWindow()) != 1) {
                    game.dealerTurn(*renderer.getWindow());
                    game.decideOutcome(*renderer.getWindow());
                    sf::sleep(sf::seconds(2));
                }
                // Check if the player wants to play again
                if (game.playAgain()) {
                    game.resetGame(renderer);  // Pass renderer to reset game
                }
                else {
                    renderer.initMainMenu();  // Go back to main menu
                }
                
            }
        }

        renderer.render();
    }

    if (game.getAllCoins() == 0) {
        std::cout << "You have 0 coins" << std::endl;
        std::cout << "Game Over" << std::endl;
    }
    else {
        std::cout << "Game Over" << std::endl;
        std::cout << "You won " << game.getAllCoins() - 100 << " coins" << std::endl;
    }
    return 0;
}
