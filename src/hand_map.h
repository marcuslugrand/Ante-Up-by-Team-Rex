#include <vector>
#include <iostream>
#include "hand.h"

class Node {
public:
    std::vector<Card> first;
    int second;
    int third;
    int balance;

    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    };

    Node(std::vector<Card> key, int value, int sum) {
        first = key;
        second = value;
        third = sum;

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

    std::vector<Node*> *nodes;
    //std::vector<Node> nodes = new std::vector<Node>;

    void insert(Hand hand);

    int getnodeCount();

    int recHand(int sum, Node* root);

    Node* insertMap(Node* root, std::vector<Card> first, int value, std::vector<Node*>* nodes);
    void findQuality(int second, std::vector<Hand>& qualtoHan2, std::vector<Node*> *nodess);
    int findHand(Node* root, std::vector<Card> first, std::vector<Node*>* nodes);

    int balanceFactor(Node* root);

    Node* rotateRight(Node* node);

    //Rotates node left
    Node* rotateLeft(Node* node);

    //Rotates node left right
    Node* rotateLeftRight(Node* node);

    //Rotates node right left
    Node* rotateRightLeft(Node* node);

    void preOrder(Node* root, int second ,std::vector<Hand> &qualtoHand);

    
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

