#include "../Ante-Up-by-Team-Rex/unordered_map.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/*
	To check output (At the find_the digits directory):
		g++ -std=c++14 -Werror -Wuninitialized -o test test-unit/test.cpp && ./test
*/
/*
 * Insertion
 */
TEST_CASE("Function: insert", "[insert1]")
{
    unordered_map um;

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