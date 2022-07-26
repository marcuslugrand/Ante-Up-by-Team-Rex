#include "../src/unordered_hand_map.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <unordered_map>

/*
	To check output (At the find_the digits directory):
		g++ -std=c++14 -Werror -Wuninitialized -o test test-unit/test.cpp && ./test
*/
/*
 * Insertion
 */
TEST_CASE("Function: insert", "[insert1]")
{
    unordered_hand_map um;
    //std::unordered_map<int, int>
    std::unordered_map<int, int>::iterator it;

    std::vector<Card> cardlist;
    for(int i = 0; i < 5; ++i)
    {
        Card newCard(1, i);
        cardlist.push_back(newCard);
    }
    Hand H(cardlist, 0);

    REQUIRE(um.insert(H) == true);
}
/*
 * Search
 */
/*
 * Access
 */
