#include "unordered_map.h"
//=== Accessors ===
Hand& unordered_map::operator[](const Hand &hand)
{
    //1. Find
    //2. return ref
}
const int unordered_map::size()
{
    return size;
}
//=== Insertion ===
void unordered_map::insert(std::vector <Hand> hand)
{
    //1. Hash
    //2. Collision resolution policy
    //3. Insert
    //4. ++size
}
//=== Search ===
const int unordered_map::find(std::vector <Hand> hand)
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