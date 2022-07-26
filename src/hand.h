#pragma once
#include <vector>
struct Card {
	int suit;
	int rank;
	Card(int suit, int rank);
    bool cardCompare(Card& a);
    bool cardCompare(Card& a) const;
};

struct Hand {
	std::vector<Card> cards;
	int qualty;
	Hand(std::vector<Card> &cards, int qualty);
    bool handCompare(Hand& a);
    bool handCompare(Hand& a) const;
};
