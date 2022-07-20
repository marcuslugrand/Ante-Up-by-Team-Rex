#pragma once
#include <vector>;
struct Card {
	int suit;
	int rank;
	Card(int suit, int rank);
};

struct Hand {
	std::vector<Card> cards;
	int qualty;
	Hand(std::vector<Card> &cards, int qualty);
};

Hand::Hand(std::vector<Card> &cards, int qualty) {
	this->cards = cards;
	this->qualty = qualty;
}

Card::Card(int suit, int rank) {
	this->suit = suit;
	this->rank = rank;
}