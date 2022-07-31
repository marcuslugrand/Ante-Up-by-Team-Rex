#include "hand_map.h"

	//Constructor
	hand_map::hand_map() {
		root = nullptr;
		nodeCount = 0;
	};

	//Get the coun#include "hand_map.h"

//Constructor
hand_map::hand_map() {
	root = nullptr;
	nodeCount = 0;
	insertCount = 0;
	searchCount = 0;
};

//Get the count of nodes
int hand_map::getnodeCount() {
	return nodeCount;
};

//Returns root
Node* hand_map::intial() {
	return root;
};

//Sets root
void hand_map::setInitial(Node* root) {
	this->root = root;
}

//Finds the height of the tree
int hand_map::getHeight(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	int left = getHeight(root->left);
	int right = getHeight(root->right);
	return 1 + std::max(left, right);
}

//Is the balance factor of tree
int hand_map::balanceFactor(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	else {
		int totalHeight = getHeight(root->left) - getHeight(root->right);
		return totalHeight;
	}
}

//Rotates node right in tree
Node* hand_map::rotateRight(Node* node) {
	Node* grandChild = node->left->right;
	Node* newParent = node->left;
	newParent->right = node;
	node->left = grandChild;
	return newParent;
}

//Rotates node left in tree
Node* hand_map::rotateLeft(Node* node) {
	Node* grandChild = node->right->left;
	Node* newParent = node->right;
	newParent->left = node;
	node->right = grandChild;
	return newParent;
}

//Rotates node left right in tree
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

//Rotates node right left in tree
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

Node* hand_map::rebalance(Node* root, int& sumR) {
	if (root == nullptr) {
		return root;
	}
	root->balance = balanceFactor(root);

	int sum3 = 0;
	int	sum4 = 0;
	if (root->left != nullptr) {
		for (int i = 0; i < 5; i++) {
			sum3 = sum3 + (root->left->first.at(i).rank * 5 + root->left->first.at(i).suit * 14) * pow(53, 5 - i);
		}
	}
	else {
		sum3 = 0;
	}
	if (root->right != nullptr) {
		for (int i = 0; i < 5; i++) {
			sum4 = sum4 + (root->right->first.at(i).rank * 5 + root->right->first.at(i).suit * 14) * pow(53, 5 - i);
		}
	}
	else {
		sum4 = 0;
	}

	if (root->balance > 1 && sumR < sum3) {
		return rotateRight(root);
	}
	else if (root->balance < -1 && sumR > sum4) {
		return rotateLeft(root);
	}
	else if (root->balance > 1 && sumR > sum3) {
		return rotateLeftRight(root);
	}
	else if (root->balance < -1 && sumR < sum4) {
		return rotateRightLeft(root);
	}
	//setInitial(root);
	return root;
}

//Inserts given hand and self balances
Node* hand_map::insertMap(Node* temp, std::vector<Card> key, int value) {
	int sum1 = 0;
	int sum2 = 0;

	for (int i = 0; i < 5; i++)
		sum1 = sum1 + (key.at(i).rank * 5 + key.at(i).suit * 14) * pow(53, 5 - i);
	if (temp != nullptr)
		for (int i = 0; i < 5; i++)
			sum2 = sum2 + (temp->first.at(i).rank * 5 + temp->first.at(i).suit * 14) * pow(53, 5 - i);
	else {
		sum2 = 0; 
	}

	sumR = sum1;

	if (temp == nullptr) {
		Node* node = new Node(key, value, sum1);
		nodeCount++;
		//root = node;
		return node;
	}
	else if (sum2 > sum1) {
		temp->left = insertMap(temp->left, key, value);
	}
	else if (sum1 > sum2) {
		temp->right = insertMap(temp->right, key, value);
	}
	//rebalance(root, sum1);
	return temp;
	//
}

//Searches through all hands of matching qualities and stores in vector
void hand_map::searchAllHands(Node* root, int second, std::vector<Hand>& qualtoHan2) {
	searchCount++;
	if (root == nullptr) {
		return;
	}
	if (second == root->second) {
		Hand hand2 = Hand(root->first, root->second);
		qualtoHan2.push_back(hand2);
	}
	searchAllHands(root->left, second, qualtoHan2);
	searchAllHands(root->right, second, qualtoHan2);
}

//Recursively searches through nodes to find matching hand
int hand_map::recHand(int sum, Node* root) {
	searchCount++;
	if (root == nullptr) {
		return -1;
	}
	if (sum == root->third) {
		return root->second;
	}
	if (root->third < sum) {
		recHand(sum, root->right);
	}
	if (root->third > sum) {
		recHand(sum, root->left);
	}
}


//Searches for name matching node, prints multiple IDs with multiple matching names
int hand_map::findHand(Node* root, std::vector<Card> first) {
	int sum = 0;

	for (int i = 0; i < 5; i++)
		sum = sum + (first.at(i).rank * 5 + first.at(i).suit * 14) * pow(53, 5 - i);

	int qual = recHand(sum, root);

	return qual;
}

//Inserts each hand from main
void hand_map::insert(Hand hand)
{
	int sumi = 0;
	for (int i = 0; i < 5; i++) {
		sumi = sumi + (hand.cards.at(i).rank * 5 + hand.cards.at(i).suit * 14) * pow(53, 5 - i);
	}
	if (root == nullptr) {
		nodeCount++;
		insertCount++;
		int sumi = 0;
		
		root = new Node(hand.cards, hand.qualty, sumi);
	}
	else {
		Node* newNode = insertMap(root, hand.cards, hand.qualty);
		//rebalance(newNode, sumR);
		setInitial(newNode);
		Node* setRoot = rebalance(root, sumR);
		setInitial(setRoot);
		
		insertCount++;
	}
}

//Finds quality integer from given hand
const int hand_map::find(const Hand& hand) {
	int qual = findHand(this->root, hand.cards);
	return qual;
}

//Finds all hands of a specific quality and stores in vector to return
std::vector<Hand> hand_map::find(const int qualty) {
	std::vector<Hand> qualtoHan2;
	this->searchAllHands(root, qualty, qualtoHan2);
	return qualtoHan2;
}t of nodes
	int hand_map::getnodeCount() {
		return nodeCount;
	};

	//Returns root
	Node* hand_map::intial() {
		return root;
	};

	//Sets root
	void hand_map::setInitial(Node* root) {
		this->root = root;
	}

	//Finds the height of the tree
	int hand_map::getHeight(Node* root) {
		if (root == nullptr) {
			return 0;
		}
		int left = getHeight(root->left);
		int right = getHeight(root->right);
		return 1 + std::max(left, right);
	}

	//Is the balance factor of tree
	int hand_map::balanceFactor(Node* root) {
		if (root == nullptr) {
			return 0;
		}
		else {
			int totalHeight = getHeight(root->left) - getHeight(root->right);
			return totalHeight;
		}
	}

	//Rotates node right in tree
	Node* hand_map::rotateRight(Node* node) {
		Node* grandChild = node->left->right;
		Node* newParent = node->left;
		newParent->right = node;
		node->left = grandChild;
		return newParent;
	}

	//Rotates node left in tree
	Node* hand_map::rotateLeft(Node* node) {
		Node* grandChild = node->right->left;
		Node* newParent = node->right;
		newParent->left = node;
		node->right = grandChild;
		return newParent;
	}

	//Rotates node left right in tree
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

	//Rotates node right left in tree
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

	//Inserts given hand and self balances
	Node* hand_map::insertMap(Node* root, std::vector<Card> key, int value) {
		int sum1 = 0;
		int sum2 = 0;

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
			root->left = insertMap(root->left, key, value);
		}
		else if (sum2 < sum1) {
			root->right = insertMap(root->right, key, value);
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
		if (root->right != nullptr) {
			for (int i = 0; i < 5; i++) {
				sum4 = sum4 + root->right->first.at(i).rank + root->right->first.at(i).suit * 13;
			}
		}
		else {
			sum4 = 0;
		}

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
		return root;
	}

	//Searches through all hands of matching qualities and stores in vector
	void hand_map::searchAllHands(Node* root, int second, std::vector<Hand> &qualtoHan2) {
		if (root == nullptr) {
			return;
		}
		if (second == root->second) {
			Hand hand2 = Hand(root->first, root->second);
			qualtoHan2.push_back(hand2);
		}
		searchAllHands(root->left, second, qualtoHan2);
		searchAllHands(root->right, second, qualtoHan2);
	}

	//Recursively searches through nodes to find matching hand
	int hand_map::recHand(int sum, Node* root) {
		if (root == nullptr) {
			return -1;
		}
		if (sum == root->third){
			return root->second;
		}
		if (root->third < sum) {
			recHand(sum, root->right);
		}
		if (root->third > sum) {
			recHand(sum, root->left);
		}
	}


	//Searches for name matching node, prints multiple IDs with multiple matching names
	int hand_map::findHand(Node* root, std::vector<Card> first) {
		int sum = 0;
		
		for (int i = 0; i < 5; i++)
			sum = sum + first.at(i).rank + (first.at(i).suit * 13);

		int qual = recHand(sum, root);
		
		return qual;
	}

	//Inserts each hand from main
	void hand_map::insert(Hand hand)
	{
		Node* newRoot = insertMap(intial(), hand.cards, hand.qualty);
		setInitial(newRoot);
		
	}

	//Finds quality integer from given hand
	const int hand_map::find(const Hand & hand) {
		int qual = findHand(this->root, hand.cards);
		return qual;
	}

	//Finds all hands of a specific quality and stores in vector to return
	std::vector<Hand> hand_map::find(const int qualty) {
		std::vector<Hand> qualtoHan2;
		this->searchAllHands(root, qualty, qualtoHan2);
		return qualtoHan2;
	}
