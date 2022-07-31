#include "unordered_hand_map.h"
/*
 * Private member functions
 */
//Hash function
const size_t unordered_hand_map::hash(const Hand& hand)
{
    size_t hash = 0;

    //Hash: ((suite - 1) * 13 + rank) * 53^i
    for(int i = 0; i < hand.cards.size(); ++i)
    {
        Card card = hand.cards.at(i);
        hash += size_t(((card.suit - 1) * 13 + card.rank) * pow(53.0f, (hand.cards.size() - i)));
    }
    return hash;
}
//Reduction
const size_t unordered_hand_map::reduce(const size_t hash)
{
    return hash % handToQual.size();
}
//Collision resolution
size_t unordered_hand_map::collisionResolution(size_t index, const Hand &hand)
{
    //Probe map
    //else if map[index] is not empty: continue probing until it is empty
    int i = 0;
    int c = 1;
    while(!handToQual.at(index).first.empty())
    {
        //Compute next probe value
        index = probe(c, i, index);

        //Increment exponent and base
        ++i;
        ++c;
    }
    return index;
}
size_t unordered_hand_map::probe(const int c, const int i, const size_t index)
{
    int p = pow(c, i);

    //Roll over index if it overflows
    if((index + p) >= handToQual.capacity())
    {
        return reduce((index + p));
    }
    else
    {
        return index + p;
    }
}
//Re-hash
void unordered_hand_map::rehash()
{
    //Get new size
    size_t newSize = handToQual.capacity() * 2;

    //Empty and resize table
    handToQual.clear();
    handToQual.resize(newSize);

    //Re-set entries and load factor
    numEntries = 0;
    loadFactor = 0.0f;

    //Re-insert all key : val
    for(auto& handList : qualToHand)
    {
        for(auto& hand : handList)
        {
            //Hand h(hand.cards, hand.qualty);
            rehashInsert(hand);
        }
    }

}
void unordered_hand_map::rehashInsert(const Hand& hand)
{
    //1. Hash: Get unique hash ID, reduce to get index
    size_t h = hash(hand);
    size_t index = reduce(h);

    //If something is present at index: probe
    if(!handToQual.at(index).first.empty())
    {
        index = collisionResolution(index, hand);
    }

    //3. Insert
    //Replace with .at(index)
    //handToQual.insert((handToQual.begin() + index), std::make_pair(hand.cards, hand.qualty));
    handToQual.at(index) = (std::make_pair(hand.cards, hand.qualty));

    //Update size and load factor
    ++numEntries;
    loadFactor = double(numEntries) / double(handToQual.capacity());
}
/*
 * Public member functions
 */
//=== Constructor ===
unordered_hand_map::unordered_hand_map()
: numEntries(0),
  loadFactor(0.0f),
  handToQual(1330000),  //Closest prime to 1000
  qualToHand(10)    //# of possible hand qualities
{}
//=== Accessors ===
int unordered_hand_map::operator[](const Hand &hand)
{
    //1. Find
    return find(hand);
}
const int unordered_hand_map::size()
{
    return numEntries;
}
//=== Insertion ===
bool unordered_hand_map::insert(const Hand& hand)
{
    //1. Hash: Get unique hash ID, reduce to get index
    size_t h = hash(hand);
    size_t index = reduce(h);

    //2. Collision resolution policy
    if(find(hand) > -1)
    {
        return false;
    }

    //If something is present at index: probe
    if(!handToQual.at(index).first.empty())
    {
        index = collisionResolution(index, hand);
    }

    //3. Insert
    //Replace with .at(index)
    //handToQual.insert((handToQual.begin() + index), std::make_pair(hand.cards, hand.qualty));
    handToQual.at(index) = (std::make_pair(hand.cards, hand.qualty));

    //Update size and load factor
    ++numEntries;
    loadFactor = double(numEntries) / double(handToQual.capacity());

    //Insert into quality list
    qualToHand.at(hand.qualty).push_back(hand);

    //4. Check load factor, rebalance/rehash if necessary
    if(loadFactor > MAX_LOAD_FACTOR)
    {
        rehash();
    }

    return true;
}
//=== Search ===
const int unordered_hand_map::find(const Hand& hand)
{
    //1. Hash: Get unique hash ID, reduce to get index
    size_t h = hash(hand);
    size_t index = reduce(h);

    //2. Affirm found / probe until found
    int i = 0;
    int c = 1;
    while(!handToQual.at(index).first.empty())
    {
        //If hands are equal: return quality
        Hand hand2(handToQual.at(index).first, handToQual.at(index).second);
        if(hand.handCompare(hand2))
        {
            return hand2.qualty;
        }
        else
        {
            //probe
            index = probe(c, i, index);
        }

        //Increment exponent and base
        ++i;
        ++c;
    }
    return -1;
}
std::vector<Hand> unordered_hand_map::find(const int quality)
{
    //1. find all hands of quality
    return qualToHand.at(quality);
}