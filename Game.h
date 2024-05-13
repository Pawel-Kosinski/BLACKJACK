#include <iostream>
#include "card.h"
#include "Deck.h"
#include "Player.h"

class Game {
private:
    Deck deck;
    Player player;
    Player dealer;
    int coins = 0;
    int allCoins = 100;

public:
    Game() {
        deck.shuffledeck();
    }

    void bet() {
        cout << "You have " << allCoins << " coins." << endl;
        cout << "How much do you want to bet? " << endl;
        cin >> coins;
        if (coins > allCoins || coins <= 0) {
            cout << "You can't bet that" << endl;
            bet();
        }
        allCoins -= coins;
        coins *= 2;
    }
    void startNewGame() {
        
        bet();
        deck.shuffledeck();
        player.clearHand();
        dealer.clearHand();
        player.add_card(deck.drawCard());
        player.add_card(deck.drawCard());
        dealer.add_card(deck.drawCard());
        cout << "Dealer's one card: " << dealer.getHandValue() << endl;
        dealer.add_card(deck.drawCard());
    }

    int playerTurn() {
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
                    return 1;
                }
            }
            else if (choice == 2) {
                continueGame = false;
            }
        }
        return 0;
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
        std::cout << "Do you want to play another game? (yes/no)" << std::endl;
        std::string response;
        std::cin >> response;
        return response == "yes";
    }

    int getAllCoins() {
        return allCoins;
    }
};
#pragma once
