#include <vector>
#include "hand.h"

class map{

private:
    // Balance the tree
    void balance(map* node);
    
    //iterate through keys
    map* iterator(std::vector<Card> first);

    const map* iterator(std::vector<Card> first) const;

    void leftRot(map* a);

    void rightRot(map* x);

    // Rotate through tree
    void rotator(map* node);

    // Function to insert a value in map
    map* insertMap(std::vector<Card> first);

    // depth at node
    int depthofTree(map* node);

    // Inititialize map variables
    map* create(std::vector<Card> first);

public:
    static class map* root;
    int count;

    map* left;
    map* right;
    map* parent;
    std::vector<Card> first;
    int second;
    int depth;

    //store hands together by quality
    std::vector<std::vector<Card>> qualtoHand;

    // CHange value of key
    /*void changeKey(vector<Hand> first, int second)
    {
        map* temp = iterator(first);
        if (temp != nullptr) {
            temp->second = second;
        }
    }*/

    // Iterate through tree in order
    /*void iterforQual(map* head, int quality)
    {
        if (root == nullptr) {
        return;
        }
        if (head->second == quality) {
            qualtoHand.push_back(first);
        }
        if (head->left != nullptr) {
            iterforQual(head->left);
        }
        if (head->right != nullptr) {
            iterforQual(head->right);
        }
        
    }*/

    // Returns number of elements in the map
    int size(void);

    // Insert key and value
    void insert(Hand hand);
    const int find(const Hand& hand);

    std::vector<Hand> find(const int quality);
};

map* map::root = nullptr;
//int map::size = 0;
