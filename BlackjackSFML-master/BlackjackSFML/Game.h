#include <iostream>
#include "card.h"
#include "Deck.h"
#include "Player.h"
#include "Renderer.h" // Add Renderer header

class Game {
private:
    Deck deck;
    Player player;
    Player dealer;
    int coins = 0;
    int allCoins = 100;
    sf::Texture reversed_cardTexture;

public:
    Game() {
        deck.shuffledeck();
        if (!reversed_cardTexture.loadFromFile("reversed.png")) {
            throw std::runtime_error("Failed to load card textures!");
        }
    }
    void resetGame(Renderer& renderer) {
        deck.shuffledeck();
        player.clearHand();
        dealer.clearHand();
        coins = 0;
        renderer.initGameLoop();  // Re-initialize game loop
    }

    void bet(Renderer& renderer) {
        std::cout << "You have " << allCoins << " coins." << std::endl;
        coins = renderer.getCurrentBet();
        if (coins > allCoins || coins <= 0) {
            std::cout << "Invalid bet amount. Please adjust your bet." << std::endl;
            return;
        }
        allCoins -= coins;
        coins *= 2;
    }

    void startNewGame(sf::RenderWindow& window, Renderer& renderer) {
        std::cout << "New game! " << std::endl;
        

        // Wait for bet confirmation
        while (!renderer.isBetConfirmed()) {
            renderer.pollEvents();
            renderer.update();
            renderer.render();
        }

        bet(renderer);
        deck.shuffledeck();
        player.clearHand();
        dealer.clearHand();
        dealer.add_card(deck.drawCard());
        std::cout << "Dealer's one card: " << dealer.getHandValue() << std::endl;
        dealer.add_card(deck.drawCard());
        player.add_card(deck.drawCard());
        player.add_card(deck.drawCard());
        renderer.clearActiveElements();  // Clear betting elements
        renderer.render();
        //window.display();
    }

    void displayPlayerHand(sf::RenderWindow& window) {
        const auto& playerCards = player.getHand();
        float xPos = 10.0f;
        for (const auto& card : playerCards) {
            sf::Sprite sprite = card->getSprite();
            sprite.setPosition(xPos, 250.0f);  // Offset y-position to display below dealer's card
            window.draw(sprite);
            xPos += 150.0f;  // Space out cards
        }
        const auto& dealerCards = dealer.getHand();
        int length = dealerCards.size(), j = 1;
        xPos = 10.0f;
        while (j < length) {
            for (const auto& card : dealerCards) {
                sf::Sprite reversedSprite = card->getSprite();
                reversedSprite.setPosition(xPos, 10.0f);
                window.draw(reversedSprite);
                xPos += 150.0f;
                j++;
            }
        }
        sf::Sprite reversedSprite(reversed_cardTexture);
        reversedSprite.setPosition(xPos - 150.0f, 10.0f);
        window.draw(reversedSprite);
        window.display();
    }

    void displayEnd(sf::RenderWindow& window) {
        const auto& dealerCards = dealer.getHand();
        int length = dealerCards.size();
        float xPos = 10.0f;
        for (const auto& card : dealerCards) {
            sf::Sprite reversedSprite = card->getSprite();
            reversedSprite.setPosition(xPos, 10.0f);
            window.draw(reversedSprite);
            xPos += 150.0f;  // Space out cards
        }

        const auto& playerCards = player.getHand();
        xPos = 10.0f;
        for (const auto& card : playerCards) {
            sf::Sprite sprite = card->getSprite();
            sprite.setPosition(xPos, 250.0f);  // Offset y-position to display below dealer's card
            window.draw(sprite);
            xPos += 150.0f;  // Space out cards
        }
    }

    int playerTurn(sf::RenderWindow& window) {
        displayPlayerHand(window);
        bool continueGame = true;
        while (continueGame) {
            std::cout << "Your hand value: " << player.getHandValue() << std::endl;
            std::cout << "1. Hit" << std::endl;
            std::cout << "2. Stay" << std::endl;
            int choice;
            std::cin >> choice;
            if (choice == 1) {
                player.add_card(deck.drawCard());
                displayPlayerHand(window);
                //window.display();
                if (player.getHandValue() > 21) {
                    std::cout << "Your hand value: " << player.getHandValue() << std::endl;
                    std::cout << "Busted" << std::endl;
                    return 1;
                }
            }
            else if (choice == 2) {
                continueGame = false;
            }
        }
        return 0;
    }

    void dealerTurn(sf::RenderWindow& window) {
        while (dealer.getHandValue() < 17) {
            dealer.add_card(deck.drawCard());
            displayPlayerHand(window);
            //window.display();
            sf::sleep(sf::seconds(1));
        }
    }

    void decideOutcome(sf::RenderWindow& window) {
        displayEnd(window);
        window.display();
        std::cout << "Dealer's hand value: " << dealer.getHandValue() << std::endl;
        if (dealer.getHandValue() > 21) {
            std::cout << "Dealer is busted. You win!" << std::endl;
            allCoins += coins;
        }
        else if (player.getHandValue() > dealer.getHandValue()) {
            std::cout << "You win!" << std::endl;
            allCoins += coins;
        }
        else if (player.getHandValue() < dealer.getHandValue()) {
            std::cout << "You lose!" << std::endl;
        }
        else {
            std::cout << "Tie game." << std::endl;
            allCoins += coins / 2;
        }
    }

    bool playAgain() {
        std::cout << "Do you want to play a new game? (yes/no)" << std::endl;
        std::string response;
        std::cin >> response;
        return response == "yes";
    }

    int getAllCoins() {
        return allCoins;
    }

    Player getPlayer() {
        return player;
    }
};
