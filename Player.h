using namespace std;
class Player {

private:
	vector<unique_ptr<Card>> hand_;

public:
	void add_card(unique_ptr<Card> card) {
		hand_.push_back(std::move(card));
	}

	int getHandValue() const {
		int value = 0;
		int aces = 0;
		for (const auto& card : hand_) {
			int cardValue = card->getRank();

			if (cardValue >= 10) 
				cardValue = 10;
			else if (cardValue == ACE) {
				aces++;
				cardValue = 11;
			}
			value += cardValue;
		}

		while (value > 21 && aces > 0) {
			value -= 10;
			aces--;
		}
		return value;
	}
	void clearHand() {
		hand_.clear();
	}
};