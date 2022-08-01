#ifndef PROJECT3_RBTREE_H
#define PROJECT3_RBTREE_H

#include <vector>
#include <cmath>
#include "hand.h"

class RBTree
{
    //Colors
    enum color {RED, BLACk};

    //Internal node
    struct Node
    {
        //Children pointers
        Node* left;
        Node* right;

        //color and balance
        color c;

        //key and val
        std::pair<std::vector<Card>, int> keyVal;

        //Constructor
        Node(std::pair<std::vector<Card>, int> _keyVal): keyVal(_keyVal) {};
        Node(std::pair<std::vector<Card>, int> _keyVal, Node* _left, Node* _right): keyVal(_keyVal), left(_left), right(_right) {};
    };

    //Tree properties
    size_t height;
    size_t numNodes;
    Node* root;

    //=== Balancing ===

    //=== Check invariants ===
    //=== Coloring ===
    //=== Hashing ===
    const size_t hash(const Hand& hand);
    //=== Helpers ===
    void insertHelper(Node*& head, Node* n);
public:
    //=== Constructor ===
    RBTree();
    //=== Destructor ===
    //~RBTree
    //=== Copy + assignment operator ===
    //=== Accessors ===
    //const Node& operator[](const int& key);
    //const Node& at(const int& key);
    const int size();
    //=== Insertion ===
    const bool insert(const Hand& hand);
    //=== Removal ===
    //=== Search ===

};
#endif //PROJECT3_RBTREE_H
