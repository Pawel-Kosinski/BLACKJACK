#include <iostream>
#include "card.h"
#include "Deck.h"
#include "Player.h"

class Game {
private:
    Deck deck;
    Player player;
    Player dealer;

public:
    Game() {
        deck.shuffledeck();
    }

    void startNewGame() {
        deck.shuffledeck();
        player.clearHand();
        dealer.clearHand();
        player.add_card(deck.drawCard());
        player.add_card(deck.drawCard());
        dealer.add_card(deck.drawCard());
        cout << "Dealer's one card: " << dealer.getHandValue() << endl;
        dealer.add_card(deck.drawCard());
    }

    void playerTurn() {
        bool continueGame = true;
        while (continueGame) {
            std::cout << "Your hand value: " << player.getHandValue() << std::endl;
            std::cout << "1. Hit" << std::endl;
            std::cout << "2. Stay" << std::endl;
            int choice;
            std::cin >> choice;
            if (choice == 1) {
                player.add_card(deck.drawCard());
                if (player.getHandValue() > 21) {
                    std::cout << "Your hand value: " << player.getHandValue() << std::endl;
                    std::cout << "Busted" << std::endl;
                    continueGame = false;
                }
            }
            else if (choice == 2) {
                continueGame = false;
            }
        }
    }

    void dealerTurn() {
        while (dealer.getHandValue() < 17) {
            dealer.add_card(deck.drawCard());
        }
    }

    void decideOutcome() {
        std::cout << "Dealer's hand value: " << dealer.getHandValue() << std::endl;
        if (dealer.getHandValue() > 21) {
            std::cout << "Dealer is busted. You win!" << std::endl;
        }
        else if (player.getHandValue() > dealer.getHandValue()) {
            std::cout << "You win!" << std::endl;
        }
        else if (player.getHandValue() < dealer.getHandValue()) {
            std::cout << "You lose!" << std::endl;
        }
        else {
            std::cout << "Tie game." << std::endl;
        }
    }

    bool playAgain() {
        std::cout << "Do you want to play another game? (yes/no)" << std::endl;
        std::string response;
        std::cin >> response;
        return response == "yes";
    }
};
#pragma once
