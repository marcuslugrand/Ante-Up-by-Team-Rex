#include <vector>
#include <iostream>
#include "hand.h"

class Node {
public:
    std::vector<Card> first;
    int second;
    int balance;

    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    };

    Node(std::vector<Card> key, int value) {
        first = key;
        second = value;

        left = nullptr;
        right = nullptr;
    };
};

class hand_map {

public:
    //static class map* root;
    Node* root;
    int nodeCount;
    int depth{};
    int index = 0;
    hand_map();
    int getHeight(Node* root);
    Node* intial() { return root; };
    void setInitial(Node* root) {
        this->root = root;
    };

    std::vector<Node*> nodes;

    void insert(Hand hand);

    int getnodeCount();

    Node* insertMap(Node* root, std::vector<Card> first, int value, std::vector<Node*>& nodes);
    void findQuality(int second, std::vector<Hand>& qualtoHan2, std::vector<Node*>& nodes);
    int findHand(Node* root, std::vector<Card> first, std::vector<Node*>& nodes);

    int balanceFactor(Node* root);

    Node* rotateRight(Node* node);

    //Rotates node left
    Node* rotateLeft(Node* node);

    //Rotates node left right
    Node* rotateLeftRight(Node* node);

    //Rotates node right left
    Node* rotateRightLeft(Node* node);

    void preOrder(Node* root, std::vector<Node*>& nodes);

    
    //store hands together by quality
    std::vector<std::vector<Hand>> qualtoHand;
    
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
    const int find(const Hand& hand);

    std::vector<Hand> find(const int quality);
};

