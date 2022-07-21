#include <iostream> 
#include <fstream> 
#include <SFML/Graphics.hpp>
#include <string>
#include "hand.h"
#include <vector>
#include <unordered_map>

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

//Function taken from https://www.geeksforgeeks.org/how-to-create-an-unordered_map-of-pairs-in-c/
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);

        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }

        // If hash1 == hash2, their XOR is zero.
        return hash1;
    }
};

int main() { 
    
    //import data
    //importFile("poker-hand-training-true.data");
    //importFile("poker-hand-testing.data");
    
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Ante Up");
    
    //----Shapes---
    sf::RectangleShape divider(sf::Vector2f(10, 800));
    divider.setPosition(800, 0);

        //Table
    int offset = 380;
    sf::RectangleShape bottom(sf::Vector2f(420, 700));
    bottom.setPosition(offset,100);
    bottom.setFillColor(sf::Color::Transparent);
    bottom.setOutlineColor(sf::Color::White);
    bottom.setOutlineThickness(5);
    sf::RectangleShape top(sf::Vector2f(420, 100));
    top.setPosition(offset,0);
    top.setFillColor(sf::Color::Transparent);
    top.setOutlineColor(sf::Color::White);
    top.setOutlineThickness(5);
    sf::RectangleShape middle(sf::Vector2f(140, 700));
    middle.setPosition(offset+140,100);
    middle.setFillColor(sf::Color::Transparent);
    middle.setOutlineColor(sf::Color::White);
    middle.setOutlineThickness(5);
            //Titles
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "error!" << endl;
    }
    sf::Text title ("History", font);
    title.setPosition(540, 10);
    title.setCharacterSize(30);
    sf::Text subtitle1("Option", font);
    subtitle1.setPosition(400, 60);
    sf::Text subtitle2("Structure", font);
    subtitle2.setPosition(530, 60);
    sf::Text subtitle3("Run Time", font);
    subtitle3.setPosition(670, 60);

    //Cards
    sf::Texture allCards;
    allCards.loadFromFile("cards.png");
    unordered_map<pair<int, int>, sf::Sprite,hash_pair> cardImages;
    for (int suit = 1; suit <= 4; suit++) {
        for (int rank = 1; rank <= 13; rank++) {
            sf::Sprite temp(allCards, sf::IntRect(73 * (rank - 1), 98 * (suit - 1), 73, 98));
            int suitReal;
            if (suit == 1)
                suitReal = 4;
            if (suit == 2)
                suitReal = 2;
            if (suit == 3)
                suitReal = 1;
            if (suit == 4)
                suitReal = 3;
            cardImages[make_pair(suitReal, rank)] = temp;
        }
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(divider);
        window.draw(bottom);
        window.draw(top);
        window.draw(middle);
        window.draw(title);
        window.draw(subtitle1);
        window.draw(subtitle2);
        window.draw(subtitle3);
        
        cardImages[make_pair(2, 1)].setPosition(900, 400);
        window.draw(cardImages[make_pair(2, 1)]);
        window.display();
    }

    return 0;
}