#include "hand_map.h"
#include <iterator>
#include <string>
#include <functional>
#include <vector>
#include <iostream>


	hand_map::hand_map() {
		nodes =  new std::vector<Node*>;
		root = nullptr;
		nodeCount = 0;
	};

	//Get the count of nodes
	int hand_map::getnodeCount() {
		return nodeCount;
	};

	//Finds the height of the tree
	int hand_map::getHeight(Node* root) {
		if (root == nullptr) {
			return 0;
		}
		int left = getHeight(root->left);
		int right = getHeight(root->right);
		return 1 + std::max(left, right);
	}

	//Is the balance factor
	int hand_map::balanceFactor(Node* root) {
		if (root == nullptr) {
			return 0;
		}
		else {
			int totalHeight = getHeight(root->left) - getHeight(root->right);
			return totalHeight;
		}
	}

	//Rotates node right
	Node* hand_map::rotateRight(Node* node) {
		Node* grandChild = node->left->right;
		Node* newParent = node->left;
		newParent->right = node;
		node->left = grandChild;
		return newParent;
	}

	//Rotates node left
	Node* hand_map::rotateLeft(Node* node) {
		Node* grandChild = node->right->left;
		Node* newParent = node->right;
		newParent->left = node;
		node->right = grandChild;
		return newParent;
	}

	//Rotates node left right
	Node* hand_map::rotateLeftRight(Node* node) {
		Node* greatGrandChild = node->left->right->left;
		Node* newChild = node->left->right;
		Node* grandChild = node->left;
		node->left = newChild;
		newChild->left = grandChild;
		grandChild->right = greatGrandChild;
		Node* newParent = rotateRight(node);
		return newParent;
	}

	//Rotates node right left
	Node* hand_map::rotateRightLeft(Node* node) {
		Node* greatGrandChild = node->right->left->right;
		Node* newChild = node->right->left;
		Node* grandChild = node->right;
		node->right = newChild;
		newChild->right = grandChild;
		grandChild->left = greatGrandChild;
		Node* newParent = rotateLeft(node);
		return newParent;
	}

	//Inserts name and ID into node and self balances
	Node* hand_map::insertMap(Node* root, std::vector<Card> key, int value, std::vector<Node*> *nodes) {
		int sum1 = 0;
		int sum2 = 0;

		//std::cout << value << std::endl;

		for (int i = 0; i < 5; i++)
			sum1 = sum1 + key.at(i).rank + (key.at(i).suit * 13);
		if (root != nullptr)
			for (int i = 0; i < 5; i++)
				sum2 = sum2 + root->first.at(i).rank + root->first.at(i).suit * 13;
		else {
			sum2 = 0;
		}
		if (root == nullptr) {
			Node* node = new Node(key, value, sum1);
			nodeCount++;
			return node;
		}
		else if (sum2 > sum1) {
			root->left = insertMap(root->left, key, value, nodes);
		}
		else if (sum2 < sum1) {
			root->right = insertMap(root->right, key, value, nodes);
		}
		else {
			return root;
		}
		
		root->balance = balanceFactor(root);
		
		int sum3 = 0;
		int	sum4 = 0;
		if (root->left != nullptr){
			for (int i = 0; i < 5; i++) {
				sum3 = sum3 + root->left->first.at(i).rank + root->left->first.at(i).suit * 13;
			}
		}
		else {
			sum3 = 0;
		}
		if (root->right != nullptr)
			for (int i = 0; i < 5; i++)
				sum4 = sum4 + root->right->first.at(i).rank + root->right->first.at(i).suit * 13;
		else
			sum4 = 0;
		
		if (root->balance > 1 && sum1 < sum3) {
			return rotateRight(root);
		}
		else if (root->balance < -1 && sum1 > sum4) {
			return rotateLeft(root);
		}
		else if (root->balance > 1 && sum1 > sum3) {
			return rotateLeftRight(root);
		}
		else if (root->balance < -1 && sum1 < sum4) {
			return rotateRightLeft(root);
		}
		//root = this->root;
		//preOrder(root, nodes);
		//std::cout << nodes.size() << std::endl;
		return root;
	}

	//Pushes nodes in vector preordered
	void hand_map::preOrder(Node* root, int second, std::vector<Hand> &qualtoHan2) {
		if (root == nullptr) {
			//std::cout << root->second << std::endl;
			return;
		}
		//nodes->push_back(root);
		//std::cout << root->second << std::endl;
		//std::cout << nodes->size() << std::endl;
		if (second == root->second) {
			Hand hand2 = Hand(root->first, root->second);
			qualtoHan2.push_back(hand2);
		}
		preOrder(root->left, second, qualtoHan2);
		preOrder(root->right, second, qualtoHan2);
	}

	

	//Searches for ID, prints name from ID
	void hand_map::findQuality(int second, std::vector<Hand>& qualtoHan2, std::vector<Node*> *nodes) {
		int n = 0;
		this->preOrder(root, second, qualtoHan2);
		//std::cout << nodes->size() << std::endl;
		/*while (n < nodes->size()) {
			Hand hand2 = Hand(nodes->at(n)->first, nodes->at(n)->second);
			qualtoHan2.push_back(hand2);
			n++;
			//std::cout << nodes->at(n)->second << std::endl;
		}*/
	}

	int hand_map::recHand(int sum, Node* root) {
		if (root == nullptr) {
			return -1;
		}
		if (sum == root->third){
			return root->second;
		}
		if (root->third > sum) {
			recHand(sum, root->right);
		}
		if (root->third < sum) {
			recHand(sum, root->left);
		}
	}


	//Searches for name matching node, prints multiple IDs with multiple matching names
	int hand_map::findHand(Node* root, std::vector<Card> first, std::vector<Node*> *nodes) {

		//std::vector<Node*> nodes;

		//preOrder(root, nodes);

		int sum = 0;
		int sum2 = 0;
		//std::cout << nodes->size() << std::endl;
		for (int i = 0; i < 5; i++)
			sum = sum + first.at(i).rank + (first.at(i).suit * 13);

		int qual = recHand(sum, root);
		//recursive function
		//
		
		
		return qual;
	}

	void hand_map::insert(Hand hand)
	{
		Node* newRoot = insertMap(intial(), hand.cards, hand.qualty, nodes);
		setInitial(newRoot);
		
	}

	const int hand_map::find(const Hand & hand) {
		//preOrder(root, nodes);
		int qual = findHand(this->root, hand.cards, nodes);
		std::cout << qual << std::endl;
		return qual;
		/*int n = 0;

		std::vector<Node*> nodes;
		std::vector<Node*> nameSame;

		preOrder(root, nodes);

		while (n < nodes.size()) {
			if (nodes[n]->first == hand.cards) {
				nameSame.push_back(nodes[n]);
				return nodes[n]->second;
			}
			n++;
		}*/
	}


	std::vector<Hand> hand_map::find(const int qualty) {
		std::vector<Hand> qualtoHan2;
		this->preOrder(root, qualty, qualtoHan2);
		return qualtoHan2;
	}
