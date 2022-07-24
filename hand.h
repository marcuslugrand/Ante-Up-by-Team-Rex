#pragma once
#include <vector>
struct Card {
	int suit;
	int rank;
	Card(int suit, int rank);
    bool cardCompare(Card& a, Card& b);
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

bool Card::cardCompare(Card& a, Card& b)
{
    if(a.suit != b.suit || a.rank != b.rank)
        return false;
    return true;
}