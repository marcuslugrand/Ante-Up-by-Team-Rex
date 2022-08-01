#include "RBTree.h"
//=== Hashing ===
const size_t RBTree::hash(const Hand& hand)
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
//=== Helpers ===
void RBTree::insertHelper(Node *&head, Hand& hand)
{
    if(root == nullptr)
        root = new Node(std::make_pair(hand.cards, hand.qualty));
}
//=== Coloring ===
//=== Constructor ===
RBTree::RBTree()
: root(nullptr),
  height(0),
  numNodes(0)
{}
//=== Destructor ===
//=== Accessors ===
const int RBTree::size()
{
    return numNodes;
}
//=== Insertion ===
const bool RBTree::insert(const Hand &hand)
{
    if(root == nullptr)
    {
        root = newNode;
        ++numNodes;
    }
    else
    {
        //Search for node
        //If not found ->insert
        //else return false

    }

    delete newNode;
}
//=== Search ===
