enum Rank {
	ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
};
enum Suit {
    CLUBS, DIAMONDS, HEARTS, SPADES
};

class Card {
private:
    Rank rank_;
    Suit suit_;
    sf::Sprite sprite_;

public:
    Card(Rank rank, Suit suit, const sf::Texture& texture, sf::IntRect textureRect)
        : rank_(rank), suit_(suit) {
        sprite_.setTexture(texture);
        sprite_.setTextureRect(textureRect);
    }

    Rank getRank() const { return rank_; }
    Suit getSuit() const { return suit_; }
    const sf::Sprite& getSprite() const { return sprite_; }
    Card(const Card& other)
        : rank_(other.rank_), suit_(other.suit_), sprite_(other.sprite_) {}
};
