#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;
class Deck {
private:
	vector<unique_ptr<Card>> cards_;

public:
	Deck() {
		for (int suit = HEARTS; suit <= SPADES; suit++) 
			for (int rank = ACE; rank <= KING; rank++)
				cards_.push_back(make_unique<Card>(static_cast<Rank>(rank), static_cast<Suit>(suit)));
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