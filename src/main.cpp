#include <iostream> 
#include <fstream> 
#include <SFML/Graphics.hpp>
#include <string>
#include "hand.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

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
    
    sf::RenderWindow window(sf::VideoMode(1800, 800), "Ante Up");
    
    //Divider
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
    sf::Text option("Options", font);
    option.setPosition(120, 1);
    sf::Text option1("How good is this hand?", font);
    option1.setPosition(40, 47);
    option1.setCharacterSize(20);
    sf::Text option2("What hands are this good?", font);
    option2.setPosition(40, 97);
    option2.setCharacterSize(20);

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
    
    //Selection
    sf::RectangleShape select(sf::Vector2f(73, 98));
    select.setFillColor(sf::Color::Transparent);
    select.setOutlineColor(sf::Color::Green);
    select.setOutlineThickness(2);

    //Options
    sf::RectangleShape button1(sf::Vector2f(20, 20));
    button1.setFillColor(sf::Color::Transparent);
    button1.setOutlineColor(sf::Color::White);
    button1.setOutlineThickness(1);
    button1.setPosition(10, 50);
    sf::RectangleShape button2(sf::Vector2f(20, 20));
    button2.setFillColor(sf::Color::Transparent);
    button2.setOutlineColor(sf::Color::White);
    button2.setOutlineThickness(1);
    button2.setPosition(10, 100);
    sf::RectangleShape button3(sf::Vector2f(20, 20));
    button3.setFillColor(sf::Color::Transparent);
    button3.setOutlineColor(sf::Color::White);
    button3.setOutlineThickness(1);
    button3.setPosition(10, 150);
    sf::RectangleShape button4(sf::Vector2f(20, 20));
    button4.setFillColor(sf::Color::Transparent);
    button4.setOutlineColor(sf::Color::White);
    button4.setOutlineThickness(1);
    button4.setPosition(10, 200);

    bool displayCards = false;
    unordered_set<pair<short, short>, hash_pair> selectedCards;
    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonReleased) {

                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    //option 1
                    if (mousePosition.y < 70 && mousePosition.y > 50 && mousePosition.x < 30 && mousePosition.x > 10) {
                        button1.setFillColor(sf::Color::White);
                        button2.setFillColor(sf::Color::Transparent);
                        button3.setFillColor(sf::Color::Transparent);
                        button4.setFillColor(sf::Color::Transparent);
                        displayCards = true;
                    }
                    //option 2
                     if (mousePosition.y < 120 && mousePosition.y > 100 && mousePosition.x < 30 && mousePosition.x > 10) {
                        button1.setFillColor(sf::Color::Transparent);
                        button2.setFillColor(sf::Color::White);
                        button3.setFillColor(sf::Color::Transparent);
                        button4.setFillColor(sf::Color::Transparent);
                    }
                     /*//option 3
                    if (mousePosition.y < game.GetHeight() * 32 && game.state == 1) {

                    }
                    //option 4
                    if (mousePosition.y < game.GetHeight() * 32 && game.state == 1) {

                    }
                    *///cards
                     if (mousePosition.y > 100 && mousePosition.y < 500 && mousePosition.x > 820 && mousePosition.x < 1780) {
                         short suit = (mousePosition.y - 100) / 100 + 1;
                         short rank = (mousePosition.x - 820) / 75 + 1;
                         if (selectedCards.find(make_pair(suit, rank)) == selectedCards.end()) {
                             selectedCards.insert(make_pair(suit, rank));
                         }
                         else {
                             selectedCards.erase(make_pair(suit, rank));
                         }
                    }
                    
                }
            }
        }

        window.clear();
        
        //draw static elements
        window.draw(divider);
        window.draw(bottom);
        window.draw(top);
        window.draw(middle);
        window.draw(title);
        window.draw(subtitle1);
        window.draw(subtitle2);
        window.draw(subtitle3);
        window.draw(button1);
        window.draw(button2);
        window.draw(button3);
        window.draw(button4);
        window.draw(option1);
        window.draw(option2);
        window.draw(option);

        //draw dynamic elements
        if(displayCards){
            for (int suit = 1; suit <= 4; suit++) {
                for (int rank = 1; rank <= 13; rank++) {
                    cardImages[make_pair(suit, rank)].setPosition(820 + 75 * (rank - 1), 100 * suit);
                    window.draw(cardImages[make_pair(suit, rank)]);
                }
            }

            for (auto cards : selectedCards) {
                select.setPosition(820 + 75 * (cards.second - 1), 100 * cards.first);
                window.draw(select);
                cout << 820 + 75 * (cards.second - 1) << " " << 100 * cards.first << endl;
            }
        }
        
        window.display();
    }

    return 0;
}