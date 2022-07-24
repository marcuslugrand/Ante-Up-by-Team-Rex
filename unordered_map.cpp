#include <cmath>
#include "unordered_map.h"
/*
 * Private member functions
 */
//Hash function
const size_t unordered_map::hash(const Hand& hand)
{
    size_t hash;

    //Hash: ((suite - 1) * 13 + rank) * 53^i
    for(int i = 0; i < hand.cards.size(); ++i)
    {
        Card& card = hand.cards.at(i);
        hash += size_t(((card.suite - 1) * 13 + card.rank) * pow(53.0f, (hand.cards.size() - i)));
    }
    return hash;
}
//Reduction
const size_t unordered_map::reduce(const size_t& hash)
{
    return hash % handToQual.size();
}
/*
 * Public member functions
 */
//=== Constructor ===
unordered_map::unordered_map()
: size = 0,
  loadFactor = 0.0f;
{}
//=== Accessors ===
Hand& unordered_map::operator[](const Hand &hand)
{
    //1. Find
    //2. return ref
}
const int unordered_map::size()
{
    return numEntries;
}
//=== Insertion ===
bool unordered_map::insert(const Hand& hand)
{
    //1. Hash: Get unique hash ID, reduce to get index
    size_t hash = hash(hand);
    size_t index = reduce(hash);

    //2. Collision resolution policy
    //If something is present at index: probe

    //3. Insert

    ++numEntries;

    //4. Check load factor, rebalance/rehash if necessary
}
//=== Search ===
const int unordered_map::find(const Hand& hand)
{
    //1. Hash
    //2. Affirm found / probe until found
    //3. return hand.qualty
}
std::vector<Hand> unordered_map::find(const int &quality)
{
    //1. find all hands of quality
    //2. push to vector of hands
    //3. return vector
}