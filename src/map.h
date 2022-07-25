#include <vector>
#include <map>
#include "hand.h"

class map{

private:
	
	int size:
	std::map<std::vector<Hand>, int> mapHand;

public:

	void insert(std::vector<Hand> hand);
	
	std::vector<Card> find(std::vector<Hand> hand);
	const int find(const int &quality);
	
};