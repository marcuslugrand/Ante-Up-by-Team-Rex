#include "hand_map.h"
#include <iterator>
#include <string>
#include <functional>
#include <vector>


hand_map::hand_map() : qualtoHand(10)
{
    int count = 0;
    int depth = 1;
    root = nullptr;
    //parent = nullptr;
}

void hand_map::balance(Node* node)
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

Node* hand_map::iterator(std::vector<Card>& first)
{
    Node* tmp = root;

    int sum1 = 0;
    int sum2 = 0;

    for (int i = 0; i < 5; i++) {
        sum1 = sum1 + first.at(i).rank + (first.at(i).suit * 13);
    }
    if (tmp != nullptr) {
        for (int i = 0; i < 5; i++) {
            sum2 = sum2 + tmp->_first.at(i).rank + tmp->_first.at(i).suit * 13;
        }
    }
    else {
        sum2 = 0;
    }

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

const Node* hand_map::iterator(std::vector<Card>& first) const
{
    Node* tmp = root;

    int sum1 = 0;
    int sum2 = 0;

    for (int i = 0; i < 5; i++) {
        sum1 = sum1 + first.at(i).rank + (first.at(i).suit * 13);
    }
    if (tmp != nullptr) {
        for (int i = 0; i < 5; i++) {
            sum2 = sum2 + tmp->_first.at(i).rank + tmp->_first.at(i).suit * 13;
        }
    }
    else {
        sum2 = 0;
    }

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

void hand_map::leftRot(Node* a)
{
    Node* b = a->right;
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

void hand_map::rightRot(Node* x)
{
    Node* y = x->left;
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

void hand_map::rotator(Node* node) {
    if (depthofTree(node->left) - depthofTree(node->right) > 1) {
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

Node* hand_map::insertMap(Node *root, std::vector<Card> first, int second)
{
    count++;
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode = new Node(first, second);
    if (root == nullptr) {
        root = newNode;
        depth = 1;
        return root;
    }
    Node* temp = root;
    Node* prev = nullptr;

    int sum1 = 0;
    int sum2 = 0;

    for (int i = 1; i <= 5 ; i++) {
        sum1 = sum1 + first[i].rank + (first[i].suit * 13);
    }
    if (temp != nullptr) {
        for (int i = 1; i <= 5; i++) {
            sum2 = sum2 + temp->_first[i].rank + temp->_first[i].suit * 13;
        }
    }
    else {
        sum2 = 0;
    }

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

int hand_map::depthofTree(Node* node) {
    if (node == nullptr) {

        // If it is null node
        return 0;
    }
    return node->depth;
}

Node* hand_map::create(std::vector<Card> first, int second)
{
    //Node* newnode = (Node*)malloc(sizeof(Node));
    Node* newnode = new Node(first, second);
    //newnode->_first = first;
    //newnode->second = second;
    return newnode;
    
}

int hand_map::size(void) {
    return count;
}

void hand_map::insert(Hand hand)
{
    std::vector<Card> tmpFirst = hand.cards;
    int tmpSecond = hand.qualty;
    insertMap(root, tmpFirst, tmpSecond);
    /*Node* temp = iterator(tmpFirst);
    if (temp == nullptr) {
        
    }
    else {
        temp->second = tmpSecond;
    }*/
    qualtoHand.at(hand.qualty).push_back(hand);
}

const int hand_map::find(const Hand& hand) {
    std::vector<Card> tmpFirst = hand.cards;
    int qual = iterator(tmpFirst)->second;
    return qual;
}

std::vector<Hand> hand_map::find(const int qualty) {
    //map* head = root;
    //iterforQual(head, qualty);
    int qTemp = qualty;
    return qualtoHand.at(qTemp);
}
