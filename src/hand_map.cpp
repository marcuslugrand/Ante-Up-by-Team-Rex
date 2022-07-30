#include "hand_map.h"
#include <iterator>
#include <string>
#include <functional>
#include <vector>
#include <iostream>


	hand_map::hand_map() {
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
	Node* hand_map::insertMap(Node* root, std::vector<Card> first, int value, std::vector<Node*>& nodes) {
		int sum1 = 0;
		int sum2 = 0;
		for (int i = 0; i < 5; i++)
			sum1 = sum1 + first.at(i).rank + (first.at(i).suit * 13);
		if (root != nullptr)
			for (int i = 0; i < 5; i++)
				sum2 = sum2 + root->first.at(i).rank + root->first.at(i).suit * 13;
		else {
			sum2 = 0;
		}
		if (root == nullptr) {
			Node* node = new Node(first, value);
			nodeCount++;
			return node;
		}
		else if (sum2 > sum1) {
			root->left = insertMap(root->left, first, value, nodes);
		}
		else if (sum2 < sum1) {
			root->right = insertMap(root->right, first, value, nodes);
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

		preOrder(root, nodes);
		//std::cout << nodes.size() << std::endl;
		return root;
	}

	//Pushes nodes in vector preordered
	void hand_map::preOrder(Node* root, std::vector<Node*>& nodes) {
		if (root == nullptr) {
			return;
		}
		nodes.push_back(root);
		preOrder(root->left, nodes);
		preOrder(root->right, nodes);
	}

	//Searches for ID, prints name from ID
	void hand_map::findQuality(int second, std::vector<Hand>& qualtoHan2, std::vector<Node*> &nodes) {
		int n = 0;
		//preOrder(root, nodes);
		std::cout << nodes.size() << std::endl;
		while (n < nodes.size()) {
			Hand hand2 = Hand(nodes[n]->first, nodes[n]->second);
			qualtoHan2.push_back(hand2);
			n++;
			std::cout << "Check 1" << std::endl;
		}
	}


	//Searches for name matching node, prints multiple IDs with multiple matching names
	int hand_map::findHand(Node* root, std::vector<Card> first, std::vector<Node*> &nodes) {
		int n = 0;

		//std::vector<Node*> nodes;

		//preOrder(root, nodes);

		int sum1 = 0;
		int sum2 = 0;
		std::cout << nodes.size() << std::endl;
		for (int i = 0; i < 5; i++)
			sum1 = sum1 + first.at(i).rank + (first.at(i).suit * 13);

		while (n < nodes.size()) {
			sum2 = 0;
			//Hand hand2 = Hand(nodes[n]->first, nodes[n]->second);
			for (int i = 0; i < 5; i++)
				sum2 = sum2 + nodes[n]->first.at(i).rank + nodes[n]->first.at(i).suit * 13;
			if (sum2 == sum1) {
					//nameSame.push_back(nodes[n]);

				return nodes[n]->second;
				}
			n++;
		}
		return -1;
	}

	//Removes node that matches ID
	/*Node* remove(Node* root, int second) {
		if (root == nullptr) {
			return nullptr;
		}
		if (second > root->second) {
			root->right = remove(root->right, second);
		}
		else if (second < root->second) {
			root->left = remove(root->left, second);
		}
		else {
			nodeCount--;
			if (root->left == nullptr && root->right == nullptr) {
				delete root;
				root = nullptr;
				return root;
			}
			else if (root->left == nullptr) {
				Node* temp = root;
				root = root->right;
				delete temp;
				return root;
			}
			else if (root->right == nullptr) {
				Node* temp = root;
				root = root->left;
				delete temp;
				return root;
			}
			else {
				Node* temp = successorCheck(root->right);
				root->second = temp->second;
				root->first = temp->first;
				root->right = remove(root->right, root->second);
				return root;
			}
		}
		return root;
	}

//Excutes functions for AVL tree
	void executeAVL(std::string action, hand_map& map) {
		int second;
		std::string temp;
		std::string first;

		int count = action.find_first_of(' ');
		std::string function = action.substr(0, count);
		action = action.substr(count + 1);

		//Insert function
		if (function == "insert") {
			action = action.substr(1);
			count = action.find_first_of('\"');
			first = action.substr(0, count);
			temp = action.substr(count + 2);

			if (isGoodNameCheck(first) == true && idCheck(temp) == true) {
				second = stoi(temp);
				Node* newRoot = map.insertMap(map.intial(), first, second);
				map.setInitial(newRoot);
			}
			else {
				std::cout << "unsuccessful" << std::endl;
			}
		}

		//Search functions for name and ID
		else if (function == "search") {
			if (action[0] == '"') {
				first = action.substr(1, action.length() - 2);
				if (isGoodNameCheck(first) == true) {
					map.searchName(map.intial(), first);
				}
				else {
					std::cout << "unsuccessful" << std::endl;
				}
			}
			else {
				if (idCheck(action) == true) {
					second = stoi(action);
					map.searchID(map.intial(), second);
				}
				else {
					std::cout << "unsuccessful" << std::endl;
				}
			}
		}

		//Prints the tree preordered
		else if (function == "printPreorder") {
			map.printPreorder(map.intial());
			std::cout << std::endl;
		}

		//Prints the tree inordered
		else if (function == "printInorder") {
			map.printInorder(map.intial());
			std::cout << std::endl;
		}

		//Prints the tree postordered
		else if (function == "printPostorder") {
			map.printPostorder(map.intial());
			std::cout << std::endl;
		}

		//Prints the amount of levels
		else if (function == "printLevelCount") {
			map.printLevelCount(map.intial());
		}

		//Removes the Nth node from the tree in order.
		else if (function == "removeInorder") {
			if (isGoodOrderCheck(action) == true) {
				int x = stoi(action);
				map.setInitial(map.removeInorder(map.intial(), x));
			}
			else {
				std::cout << "unsuccessful" << std::endl;
			}
		}
	}*/

	void hand_map::insert(Hand hand)
	{
		std::vector<Node*> nodess;
		//std::cout << "Check 1" << std::endl;
		//std::cout << "Check 2" << std::endl;
		Node* newRoot = insertMap(intial(), hand.cards, hand.qualty, nodes);
		//std::cout << "Check 3" << std::endl;
		setInitial(newRoot);
		preOrder(root, nodes);
		std::cout << nodes.size() << std::endl;
		//std::cout << "Check 1" << std::endl;
		//std::cout << "Check 4" << std::endl;
		//std::vector<Card> tmpFirst = hand.cards;
		//int tmpSecond = hand.qualty;
		//insertMap(map.intial(), tmpFirst, tmpSecond);
		/*Node* temp = iterator(tmpFirst);
		if (temp == nullptr) {

		}
		else {
			temp->second = tmpSecond;
		}*/
		//qualtoHand.at(hand.qualty).push_back(hand);
	}

	const int hand_map::find(const Hand & hand) {
		
		int qual = findHand(root, hand.cards, nodes);
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
		Node* head = root;
		std::vector<Hand> qualtoHan2;
		findQuality(qualty, qualtoHan2, nodes);
		for (int i = 0; i < nodes.size(); i++) {
			Hand qualtoHan = Hand(nodes[i]->first, nodes[i]->second);
			qualtoHan2.push_back(qualtoHan);
		}
		//int qTemp = qualty;
		//index = 0;
		return qualtoHan2;
	}
