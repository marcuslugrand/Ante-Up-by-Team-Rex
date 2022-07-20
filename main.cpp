#include <iostream> 
#include <fstream> 
#include <SFML/Graphics.hpp>
#include <string>
#include "hand.h"
#include <vector>

using namespace std;

void importFile(string file) {
    ifstream data(file);
    if (data.is_open()) {
        while (!data.eof()) {
            vector<Card> cards;

            for (short i = 0; i < 5; i++) {
                string suit;
                getline(data, suit, ',');

                string rank;
                getline(data, rank, ',');
                //cout << suit << " " << rank << " | ";
                Card card = Card(stoi(suit), stoi(rank));
                cards.push_back(card);
            }
            string quality;
            getline(data, quality);
            //cout << quality << endl;

            Hand hand = Hand(cards, stoi(quality));
            //unordered_map.insert(hand);
            //map.insert(hand);
        }
    }
}
int main() { 
    
    //import data
    importFile("poker-hand-training-true.data");
    importFile("poker-hand-testing.data");
    
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Ante Up");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}