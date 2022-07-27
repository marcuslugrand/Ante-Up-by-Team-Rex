#include "map.h"
#include <iterator>


void map::balance(map* node)
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

map* map::iterator(std::vector<Card>& first)
{
    map* tmp = root;
    while (tmp != nullptr && tmp->first != first) {
        if (first < tmp->first) {
            tmp = tmp->left;
        }
        else {
            tmp = tmp->right;
        }
    }
    return tmp;
}

const map* map::iterator(std::vector<Card>& first) const
{
    map* tmp = root;
    while (tmp != nullptr && tmp->first != first) {
        if (first < tmp->first) {
            tmp = tmp->left;
        }
        else {
            tmp = tmp->right;
        }
    }
    return tmp;
}

void map::leftRot(map* a)
{
    map* b = a->right;
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

void map::rightRot(map* x)
{
    map* y = x->left;
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

void map::rotator(map* node) {
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

map* map::insertMap(std::vector<Card> first)
{
    count++;
    map* newNode = create(first);
    if (root == nullptr) {
        root = newNode;
        return root;
    }
    map* temp = root;
    map* prev = nullptr;
    while (temp != nullptr) {
        prev = temp;

        if (first < temp->first) {
            temp = temp->left;
        }
        else if (first > temp->first) {
            temp = temp->right;
        }
        else {
            free(newNode);
            count--;
            return temp;
        }
    }
    if (first < prev->first) {
        prev->left = newNode;
    }
    else {
        prev->right = newNode;
    }
    newNode->parent = prev;
    balance(newNode);
    return newNode;
}

int map::depthofTree(map* node)
{
    if (node == nullptr) {

        // If it is null node
        return 0;
    }
    return node->depth;
}

map* map::create(std::vector<Card> first)
{
    map* newnode = (map*)malloc(sizeof(map));
    newnode->first = first;
    newnode->second = 0;
    newnode->left = nullptr;
    newnode->right = nullptr;
    newnode->parent = nullptr;
    newnode->depth = 1;
    return newnode;
}

int map::size(void) {
    return count;
}

void map::insert(Hand hand)
{
    first = hand.cards;
    second = hand.qualty;

    map* temp = iterator(first);
    if (temp == nullptr) {
        insertMap(first)->second = hand.qualty;
    }
    else {
        temp->second = second;
    }
    qualtoHand.at(second).push_back(hand);

}

const int map::find(const Hand& hand) {
    first = hand.cards;
    int qual = iterator(first)->second;
    return qual;
}

std::vector<Hand> map::find(const int qualty) {
    //map* head = root;
    //iterforQual(head, qualty);
    int qTemp = qualty;
    return qualtoHand.at(qTemp);
}
