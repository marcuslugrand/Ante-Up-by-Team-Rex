#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include "hand.h"

//Node class for tree
class Node {
public:
    std::vector<Card> first;
    int second;
    size_t third;
    int balance;

    Node* left;
    Node* right;

    Node(std::vector<Card> key, int value, size_t sum) {
        first = key;
        second = value;
        third = sum;

        left = nullptr;
        right = nullptr;
    };
};

//Map class for main
class hand_map {
private:
    

public:
    Node* root;
    int nodeCount;
    int insertCount;
    int searchCount;
    int depth{};
    size_t sumR;
    int recursion;
    
    
    hand_map();

    int getHeight(Node* root);
    Node* intial();
    void setInitial(Node* root);

    int getnodeCount();
    //int getHeight(Node* node);

    int recHand(size_t sum, Node* root, int &recursion);
    void searchAllHands(Node* root, int second ,std::vector<Hand> &qualtoHand);
    
    Node* insertMap(Node* root, std::vector<Card> first, size_t value);
    void findQuality(int second, std::vector<Hand>& qualtoHan2);
    size_t findHand(Node* root, std::vector<Card> first);

    int balanceFactor(Node* root);
    Node* rebalance(Node* node, size_t& sumR);

    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);
    
    void insert(Hand hand);
    const int find(const Hand& hand);
    std::vector<Hand> find(const int quality);
};

