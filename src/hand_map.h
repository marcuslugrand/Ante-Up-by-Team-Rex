#include <vector>
#include <iostream>
#include <string>
#include "hand.h"

//Node class for tree
class Node {
public:
    std::vector<Card> first;
    int second;
    int third;
    int balance;

    Node* left;
    Node* right;

    Node() {
        int second = 0;
        int third = 0;
        int balance = 0;
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

//Map class for main
class hand_map {
public:
    Node* root;
    int nodeCount;
    int depth{};

    std::vector<Node*> *nodes;
    
    hand_map();

    int getHeight(Node* root);
    Node* intial();
    void setInitial(Node* root);

    int getnodeCount();

    int recHand(int sum, Node* root);
    void searchAllHands(Node* root, int second ,std::vector<Hand> &qualtoHand);
    
    Node* insertMap(Node* root, std::vector<Card> first, int value);
    void findQuality(int second, std::vector<Hand>& qualtoHan2);
    int findHand(Node* root, std::vector<Card> first);

    int balanceFactor(Node* root);

    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);
    
    void insert(Hand hand);
    const int find(const Hand& hand);
    std::vector<Hand> find(const int quality);
};

