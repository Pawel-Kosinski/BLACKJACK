#include <iostream>
#include "card.h"
#include "Deck.h"
#include "Player.h"

using namespace std;

int main() {
    bool playAgain = true;
    while (playAgain) {
        cout << endl;
        cout << "New game" << endl;
        Deck deck;
        deck.shuffledeck();

        Player player;
        Player dealer;
        player.add_card(deck.drawCard());
        player.add_card(deck.drawCard());

        dealer.add_card(deck.drawCard());
        cout << "Dealer's one card: " << dealer.getHandValue() << endl;
        dealer.add_card(deck.drawCard());

        bool continueGame = true;
        while (continueGame) {
            cout << "Your hand value: " << player.getHandValue() << endl;
            cout << "What do you want to do? " << endl;
            cout << "1. Hit" << endl;
            cout << "2. Stay" << endl;
            int choice;
            cin >> choice;
            switch (choice) {
            case 1:
                player.add_card(deck.drawCard());
                if (player.getHandValue() > 21) {
                    cout << "Your hand value: " << player.getHandValue() << endl;
                    cout << "Busted" << endl;
                    continueGame = false;
                }
                break;
            case 2:
                continueGame = false;
                break;
            }
        }

        if (player.getHandValue() <= 21) {
            while (dealer.getHandValue() < 17) {
                dealer.add_card(deck.drawCard());
            }

            cout << "Dealer's hand value: " << dealer.getHandValue() << endl;
            if (dealer.getHandValue() > 21) {
                cout << "Dealer is busted. You win" << endl;
            }
            else if (player.getHandValue() > dealer.getHandValue()) {
                cout << "You win" << endl;
            }
            else if (player.getHandValue() < dealer.getHandValue()) {
                cout << "You lose" << endl;
            }
            else {
                cout << "Tie game" << endl;
            }
        }

        cout << "Do you want to play another game? (yes/no)" << endl;
        string response;
        cin >> response;
        if (response != "yes") {
            playAgain = false;
        }
    }
    cout << "Game Over" << endl;
    return 0;
}