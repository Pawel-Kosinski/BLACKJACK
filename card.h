enum Rank {
	ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
};
enum Suit {
	HEARTS, DIAMONDS, CLUBS, SPADES
};



class Card  {
private:
	Rank rank_;
	Suit suit_;

public:
	Card(Rank rank, Suit suit): rank_(rank), suit_(suit) {}

	Rank getRank() const { return rank_; }
	Suit getSuit() const { return suit_; }
};