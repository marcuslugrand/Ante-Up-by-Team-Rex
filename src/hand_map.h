#include <vector>
#include <iostream>
#include "hand.h"

class hand_map {

private:
    // Balance the tree
    void balance(hand_map* node);

    //iterate through keys
    hand_map* iterator(std::vector<Card>& first);

    const hand_map* iterator(std::vector<Card>& first) const;

    void leftRot(hand_map* a);

    void rightRot(hand_map* x);

    // Rotate through tree
    void rotator(hand_map* node);

    // Function to insert a value in map
    hand_map* insertMap(std::vector<Card> first);

    // depth at node
    int depthofTree(hand_map* node);

    // Inititialize map variables
    hand_map* create(std::vector<Card> first);

    const int search(std::vector<Card> _first) const
    {
        const hand_map* temp = iterator(_first);
        if (temp != nullptr) {
            return temp->second;
        }
        return 0;
    }

public:
    //static class map* root;
    hand_map();

    std::vector<Card> _first;
    int second{};
    int count{};
    int depth{};
    hand_map* root{};
    hand_map* left{};
    hand_map* right{};
    hand_map* parent{};



    int operator[](std::vector<Card> key) {
        return insertMap(key)->second;
    }

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
