#ifndef PROJECT3_UNORDERED_MAP_H
#define PROJECT3_UNORDERED_MAP_H

#include <vector>
#include <utility>
#include "hand.h"
class unordered_map
{
private:
    static const double MAX_LOAD_FACTOR = 0.5f;
    int size;
    double loadFactor;

    //Map Container Implementation
    std::vector<std::pair<Hand, int>> handToQual;
    std::vector<std::vector<Hand>> qualToHand;

    //Hash Function
    //Collision Resolution
    //Load Factor Re-balancing

public:
    //=== Constructor ===
    unordered_map();
    //=== Destructor ===
    //=== CopyConst + CopyAss ===
    //=== Accessors ===
    Hand& operator[](const Hand& hand);
    const int size();

    //=== Insertion ===
    bool insert(std::vector<Hand>& hand);

    //=== Search ===
    const int find(std::vector<Hand> hand);
    std::vector<Hand> find(const int& quality);
};
#endif //PROJECT3_UNORDERED_MAP_H