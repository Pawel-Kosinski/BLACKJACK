#include <vector>
#include <memory>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

class Deck {
private:
    vector<unique_ptr<Card>> cards_;
    sf::Texture cardTexture;
    
public:
    Deck() {
        if (!cardTexture.loadFromFile("cards.png")) {
            throw std::runtime_error("Failed to load card textures!");
        }

        int cardWidth = 154;
        int cardHeight = 224;

        for (int suit = 0; suit < 4; ++suit) { // Suits: 0 to 3
            for (int rank = 0; rank < 13; ++rank) { // Ranks: 0 to 12
                sf::IntRect rect(cardWidth * rank, cardHeight * suit, cardWidth, cardHeight);
                unique_ptr<Card> newCard = make_unique<Card>(static_cast<Rank>(rank + 1), static_cast<Suit>(suit), cardTexture, rect);
                cards_.push_back(std::move(newCard));
            }
        }

    }

    void shuffledeck() {
        random_device rd;
        mt19937 g(rd());
        shuffle(cards_.begin(), cards_.end(), g);
    }

    unique_ptr<Card> drawCard() {
        if (cards_.empty())
            return nullptr;

        unique_ptr<Card> card = std::move(cards_.back());
        cards_.pop_back();
        return card;
    }
};
