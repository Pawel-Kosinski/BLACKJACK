#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "Game.h"  

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "BlackJack");

    Game game;
    while (window.isOpen() && game.getAllCoins() != 0 && game.playAgain()) {  
        game.startNewGame(window);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::sleep(sf::seconds(1)); 
        game.displayPlayerHand(window);
        window.display();
        int check = game.playerTurn(window);
        if (check != 1) {
            game.dealerTurn(window);
            game.decideOutcome(window);
            sf::sleep(sf::seconds(2));
            std::cout << std::endl;
        }
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
