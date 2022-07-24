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
const size_t unordered_map::reduce(const size_t hash)
{
    return hash % handToQual.size();
}
//Collision resolution
size_t unordered_map::collisionResolution(size_t index, Hand &hand)
{
    //Probe map
    //else if map[index] is not empty: continue probing until it is empty
    int i = 0;
    int c = 1;
    while(!handToQual.at(index).first.empty())
    {
        //Compute next probe value
        index = pow(c, i, index);

        //Increment exponent and base
        ++i;
        ++c;
    }
    return index;
}
size_t unordered_map::probe(const int c, const int i, const size_t index)
{
    int p = pow(c, i);

    //Roll over index if it overflows
    if((index + probe) >= qualToHand.capacity())
    {
        return reduce((index + p));
    }
    else
    {
        return index + p;
    }
}
//Re-hash
void unordered_map::rehash()
{
    //copy all elements from handToQual to a temp vector
    std::vector<std::pair<std::vector<Card>>, int> tempList;
    for(auto& keyVal : handToQual)
    {
        if(!keyVal.first.empty())
            tempList.push_back(keyVal);
    }

    //Get new size
    size_t newSize = handToQual.capacity() * 2;

    //Empty and resize table
    handToQual.clear();
    handToQual.resize(newSize);

    //Re-insert all key : val
    for(auto& keyVal : tempList)
    {
        insert(keyVal);
    }

}
/*
 * Public member functions
 */
//=== Constructor ===
unordered_map::unordered_map()
: numEntries(0),
  loadFactor(0.0f),
  handToQual(997),  //Closest prime to 1000
  qualToHand(10)    //# of possible hand qualities
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
    if(find.(hand) > -1)
    {
        return false;
    }

    //If something is present at index: probe
    if(!handToQual.at(index).first.empty())
    {
        index = collisionResolution(index, hand);
    }

    //3. Insert
    handToQual.insert(index, std::make_pair(hand.cards, hand.qualty));

    //Update size and load factor
    ++numEntries;
    loadFactor = double(numEntries) / double(handToQual.capacity());

    //4. Check load factor, rebalance/rehash if necessary
    if(loadFactor > 0.5f)
    {
        rehash();
    }

    //Insert into quality list
    qualToHand.at(hand.qualty).push_back(hand);

    return true;
}
//=== Search ===
const int unordered_map::find(const Hand& hand)
{
    //1. Hash: Get unique hash ID, reduce to get index
    size_t hash = hash(hand);
    size_t index = reduce(hash);

    //2. Affirm found / probe until found
    int i = 0;
    int c = 1;
    while(!handToQual.at(index).first.empty())
    {
        //if whatever is present at the index == hand: return quality
        //for(int i = 0; i < hand.cards.size(); ++i)
        //{
            //Card& card1 = hand.cards.at(i);
            //Card& card2 = handToQual.at(index).first.at(i);
            //if(!card1.cardCompare(card2))
                //probe
                //break
        //}

        //If hands are equal: return quality
        if(hand->handCompare(handToQual.at(index).first))
        {
            return hand.qualty;
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
std::vector<Hand> unordered_map::find(const int quality)
{
    //1. find all hands of quality
    return qualToHand.at(quality);
}