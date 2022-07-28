#include "hand_map.h"
#include <iterator>
#include <string>
#include <functional>


void hand_map::balance(hand_map* node)
{
    while (node != root) {
        int d = node->depth;
        node = node->parent;
        if (node->depth < d + 1) {
            node->depth = d + 1;
        }
        if (node == root && depthofTree(node->left) - depthofTree(node->right) > 1) {
            if (depthofTree(node->left->left) > depthofTree(node->left->right)) {
                root = node->left;
            }
            else {
                root = node->left->right;
            }
            rotator(node);
            break;
        }
        else if (node == root && depthofTree(node->left) - depthofTree(node->right) < -1) {
            if (depthofTree(node->right->right) > depthofTree(node->right->left)) {
                root = node->right;
            }
            else {
                root = node->right->left;
            }
            rotator(node);
            break;
        }
        rotator(node);
    }
}

hand_map* hand_map::iterator(std::vector<Card>& first)
{
    hand_map* tmp = root;

    int sum1 = 0;
    int sum2 = 0;
    
    for (std::vector<Card>::iterator it = first.begin(), end = first.end(); it != end; ++it)
        sum1 = sum1 + (*it).rank + (*it).suit;
    for (std::vector<Card>::iterator it = tmp->_first.begin(), end = tmp->_first.end(); it != end; ++it)
        sum2 = sum2 + (*it).rank + (*it).suit;

    while (tmp != nullptr && sum1 != sum2) {
        if (sum1 < sum2) {
            tmp = tmp->left;
        }
        else {
            tmp = tmp->right;
        }
    }
    return tmp;
}

const hand_map* hand_map::iterator(std::vector<Card>& first) const
{
    hand_map* tmp = root;

    int sum1 = 0;
    int sum2 = 0;

    for (std::vector<Card>::iterator it = first.begin(), end = first.end(); it != end; ++it)
        sum1 = sum1 + (*it).rank + (*it).suit;
    for (std::vector<Card>::iterator it = tmp->_first.begin(), end = tmp->_first.end(); it != end; ++it)
        sum2 = sum2 + (*it).rank + (*it).suit;

    while (tmp != nullptr && sum1 != sum2) {
        if (sum1 < sum2) {
            tmp = tmp->left;
        }
        else {
            tmp = tmp->right;
        }
    }
    return tmp;
}

void hand_map::leftRot(hand_map* a)
{
    hand_map* b = a->right;
    a->right = b->left;

    if (b->left != nullptr) {
        b->left->parent = a;
    }
    if (a->parent != nullptr && a->parent->left == a) {
        a->parent->left = b;
    }
    else if (a->parent != nullptr && a->parent->right == a) {
        a->parent->right = b;
    }

    b->parent = a->parent;
    b->left = a;
    a->parent = b;
}

void hand_map::rightRot(hand_map* x)
{
    hand_map* y = x->left;
    x->left = y->right;

    if (y->right != nullptr) {
        y->right->parent = x;
    }
    if (x->parent != nullptr && x->parent->right == x) {
        x->parent->right = y;
    }
    else if (x->parent != nullptr && x->parent->left == x) {
        x->parent->left = y;
    }

    y->parent = x->parent;
    y->right = x;
    x->parent = y;
}

void hand_map::rotator(hand_map* node) {
    if (depthofTree(node->left)
        - depthofTree(node->right) > 1) {
        if (depthofTree(node->left->left) > depthofTree(node->left->right)) {
            node->depth = std::max(depthofTree(node->right) + 1, depthofTree(node->left->right) + 1);
            node->left->depth = std::max(depthofTree(node->left->left) + 1, depthofTree(node) + 1);
            rightRot(node);
        }
        else {
            node->left->depth = std::max(depthofTree(node->left->left) + 1, depthofTree(node->left->right->left) + 1);
            node->depth = std::max(depthofTree(node->right) + 1, depthofTree(node->left->right->right) + 1);
            node->left->right->depth = std::max(depthofTree(node) + 1, depthofTree(node->left) + 1);
            leftRot(node->left);
            rightRot(node);
        }
    }
    else if (depthofTree(node->left) - depthofTree(node->right) < -1) {
        if (depthofTree(node->right->right) > depthofTree(node->right->left)) {
            node->depth = std::max(depthofTree(node->left) + 1, depthofTree(node->right->left) + 1);
            node->right->depth = std::max(depthofTree(node->right->right) + 1, depthofTree(node) + 1);
            leftRot(node);
        }
        else {
            node->right->depth = std::max(depthofTree(node->right->right) + 1, depthofTree(node->right->left->right) + 1);
            node->depth = std::max(depthofTree(node->left) + 1, depthofTree(node->right->left->left) + 1);
            node->right->left->depth = std::max(depthofTree(node) + 1, depthofTree(node->right) + 1);
            rightRot(node->right);
            leftRot(node);
        }
    }
}

hand_map* hand_map::insertMap(std::vector<Card> first)
{
    count++;
    hand_map* newNode = create(first);
    if (root == nullptr) {
        root = newNode;
        return root;
    }
    hand_map* temp = root;
    hand_map* prev = nullptr;

    int sum1 = 0;
    int sum2 = 0;

    for (std::vector<Card>::iterator it = first.begin(), end = first.end(); it != end; ++it)
        sum1 = sum1 + (*it).rank + (*it).suit;
    for (std::vector<Card>::iterator it = temp->_first.begin(), end = temp->_first.end(); it != end; ++it)
        sum2 = sum2 + (*it).rank + (*it).suit;

    while (temp != nullptr) {
        prev = temp;

        if (sum1 < sum2) {
            temp = temp->left;
        }
        else if (sum1 > sum2) {
            temp = temp->right;
        }
        else {
            free(newNode);
            count--;
            return temp;
        }
    }
    if (sum1 < sum2) {
        prev->left = newNode;
    }
    else {
        prev->right = newNode;
    }
    newNode->parent = prev;
    balance(newNode);
    return newNode;
}

int hand_map::depthofTree(hand_map* node)
{
    if (node == nullptr) {

        // If it is null node
        return 0;
    }
    return node->depth;
}

hand_map* hand_map::create(std::vector<Card> first)
{
    hand_map* newnode = (hand_map*)malloc(sizeof(hand_map));
    newnode->_first = first;
    newnode->second = 0;
    newnode->left = nullptr;
    newnode->right = nullptr;
    newnode->parent = nullptr;
    newnode->depth = 1;
    return newnode;
}

int hand_map::size(void) {
    return count;
}

void hand_map::insert(Hand hand)
{
    _first = hand.cards;
    second = hand.qualty;

    hand_map* temp = iterator(_first);
    if (temp == nullptr) {
        insertMap(_first)->second = hand.qualty;
    }
    else {
        temp->second = second;
    }
    qualtoHand.at(second).push_back(hand);

}

const int hand_map::find(const Hand& hand) {
    _first = hand.cards;
    int qual = iterator(_first)->second;
    return qual;
}

std::vector<Hand> hand_map::find(const int qualty) {
    //map* head = root;
    //iterforQual(head, qualty);
    int qTemp = qualty;
    return qualtoHand.at(qTemp);
}
