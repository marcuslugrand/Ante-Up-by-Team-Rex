#pragma once

#include <vector>
#include <utility>
#include <cmath>
#include "hand.h"
class unordered_hand_map
{
private:
    static constexpr double MAX_LOAD_FACTOR = 0.75f;
    int numEntries;
    double loadFactor;

    //Map Container Implementation
    std::vector<std::pair<std::vector<Card>, int>> handToQual;
    std::vector<std::vector<Hand>> qualToHand;

    //Hash Function
    const size_t hash(const Hand& hand);

    //Reduction function
    const size_t reduce(const size_t hash);

    //Collision Resolution
    size_t collisionResolution(size_t index, const Hand& hand);
    size_t probe(const int c, const int i, const size_t index);

    //Load Factor Re-balancing
    void rehash();

public:
    //=== Constructor ===
    unordered_hand_map();

    //=== Accessors ===
    int operator[](const Hand& hand);
    const int size();

    //=== Insertion ===
    bool insert(const Hand& hand);

    //=== Search ===
    const int find(const Hand& hand);
    std::vector<Hand> find(const int quality);
};