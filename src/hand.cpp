#include "hand.h"
Hand::Hand(std::vector<Card>& cards, int qualty) {
    this->cards = cards;
    this->qualty = qualty;
}

Card::Card(int suit, int rank) {
    this->suit = suit;
    this->rank = rank;
}

bool Card::cardCompare(Card& a)
{
    /*if (this->suit != a.suit || this->rank != a.rank)
        return false;
    return true;*/
    //Just call the const version with a cast
    return static_cast<const Card&>(*this).cardCompare(a);
}

bool Card::cardCompare(Card& a) const
{
    if (this->suit != a.suit || this->rank != a.rank)
        return false;
    return true;
}

bool Hand::handCompare(Hand& a)
{
    /*for (int i = 0; i < 5; ++i)
    {
        if (!this->cards.at(i).cardCompare(a.cards.at(i)))
            return false;
    }
    return true;*/
    //Just call the const version with a cast
    return static_cast<const Hand&>(*this).handCompare(a);
}
bool Hand::handCompare(Hand& a) const
{
    for (int i = 0; i < 5; ++i)
    {
        if (!this->cards.at(i).cardCompare(a.cards.at(i)))
            return false;
    }
    return true;
}