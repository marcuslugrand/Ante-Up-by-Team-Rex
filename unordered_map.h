#ifndef PROJECT3_UNORDERED_MAP_H
#define PROJECT3_UNORDERED_MAP_H

#include <vector>
#include "hand.h"
class unordered_map
{
private:
    int size;
    //Hash Function
public:
    //=== Constructor ===
    //=== Destructor ===
    //=== CopyConst + CopyAss ===
    //=== Accessors ===
    Hand& operator[](const Hand& hand);
    const int size();
    //=== Insertion ===
    void insert(std::vector<Hand> hand);

    //=== Search ===
    const int find(std::vector<Hand> hand);
    std::vector<Hand> find(const int& quality);
};
#endif //PROJECT3_UNORDERED_MAP_H