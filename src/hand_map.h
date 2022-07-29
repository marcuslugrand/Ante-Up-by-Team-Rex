#include <vector>
#include <iostream>
#include "hand.h"

class Node {
public:
    std::vector<Card> _first;
    int second;
    int depth;

    Node* left;
    Node* right;
    Node* parent;

    Node() {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    };

    Node(std::vector<Card> first, int _second) {
        _first = first;
        second = _second;

        left = nullptr;
        right = nullptr;
        parent = nullptr;
    };
};

class hand_map {

private:
    // Balance the tree
    void balance(Node* node);

    //iterate through keys
    Node* iterator(std::vector<Card>& first);

    const Node* iterator(std::vector<Card>& first) const;

    void leftRot(Node* a);

    void rightRot(Node* x);

    // Rotate through tree
    void rotator(Node* node);

    // Function to insert a value in map
    Node* insertMap(Node *root, std::vector<Card> first, int second);

    // depth at node
    int depthofTree(Node* node);

    // Inititialize map variables
    Node* create(std::vector<Card> first, int second);

    const int search(std::vector<Card> _first) const
    {
        const Node* temp = iterator(_first);
        if (temp != nullptr) {
            return temp->second;
        }
        return 0;
    }

public:
    //static class map* root;
    Node* root;
    int count{};
    int depth{};
    
    hand_map();
    
    //Node* parent;



    //int operator[](std::vector<Card> key) {
    //    return insertMap(key)->second;
    //}

    const int operator[](std::vector<Card> key) const
    {
        // Search method is also qualified with const
        return search(key);
    }
    //store hands together by quality
    std::vector<std::vector<Hand>> qualtoHand;

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

//map* map::root = nullptr;
//int map::size = 0;#pragma once
