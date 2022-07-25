#include "map.h"
#include <map>
#include <iterator>


const int map::size()
{
    return size;
}

void map::insert(std::vector <Hand> hand)
{
    mapHand.insert(std::pair<hand.cards, hand.quality>);
    ++size;
}

const int map::find(std::vector <Hand> hand)
{
    for (auto iter = mapHand.find(hand); iter != mapHand.end(); iter++) {
        return iter -> first;
    }
}
std::vector<Hand> map::find(const int &quality)
{
    for (auto iter = mapHand.find(&quality); iter != mapHand.end(&quality); iter++) {
        hand.push_back();
    }
    return hand;
}
