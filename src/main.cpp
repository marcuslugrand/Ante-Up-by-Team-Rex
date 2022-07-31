#include <iostream> 
#include <fstream> 
#include <SFML/Graphics.hpp>
#include <string>
//#include "hand.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "Record.h"
#include "hand_map.h"
#include "unordered_hand_map.h"
#include <chrono>

using namespace std;

void importFile(string file, unordered_hand_map* hashMap, hand_map* treeMap) { //Inserts the data into the HashMap and the TreeMap
    ifstream data(file);
    if (data.is_open()) {
        while (!data.eof()) {
            vector<Card> cards;

            for (short i = 0; i < 5; i++) {
                string suit;
                getline(data, suit, ',');

                string rank;
                getline(data, rank, ',');
               // cout << suit << " " << rank << " | ";
                Card card = Card(stoi(suit), stoi(rank));
                cards.push_back(card);
            }
            string quality;
            getline(data, quality);
           // cout << quality << endl;

            Hand hand = Hand(cards, stoi(quality));
            hashMap->insert(hand);
            treeMap->insert(hand);
        }
    }
}

//Function taken from https://www.geeksforgeeks.org/how-to-create-an-unordered_map-of-pairs-in-c/ used to hash pairs
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
    unordered_hand_map* hashMap = new unordered_hand_map;
    hand_map* treeMap = new hand_map;

    //import data
    importFile("test1.data", hashMap, treeMap);
    
    sf::RenderWindow window(sf::VideoMode(1800, 800), "Ante Up");
    
    //Load Font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "error!" << endl;
    }

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
    
    //Match card Img with Card suit/rank
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
    
    //---Selection---
    unordered_set<pair<short, short>, hash_pair> selectedCardsSet;
    queue<pair<short, short>> selectedCardsQueue;
    sf::RectangleShape select(sf::Vector2f(73, 98));
    select.setFillColor(sf::Color::Transparent);
    select.setOutlineColor(sf::Color::Green);
    select.setOutlineThickness(2);
    //Selection Quantitiy
    sf::Text numSelect("", font);
    numSelect.setPosition(1250,500);
    numSelect.setCharacterSize(50);

    //Options
    sf::RectangleShape button1(sf::Vector2f(20, 20));
    button1.setFillColor(sf::Color::White);
    button1.setOutlineColor(sf::Color::White);
    button1.setOutlineThickness(1);
    button1.setPosition(10, 50);
    sf::RectangleShape button2(sf::Vector2f(20, 20));
    button2.setFillColor(sf::Color::Transparent);
    button2.setOutlineColor(sf::Color::White);
    button2.setOutlineThickness(1);
    button2.setPosition(10, 100);

    //Run
    sf::RectangleShape runButton(sf::Vector2f(100, 50));
    runButton.setFillColor(sf::Color::White);
    runButton.setOutlineColor(sf::Color::White);
    runButton.setOutlineThickness(1);
    runButton.setPosition(250, 725);
    sf::Text runText("Run", font);
    runText.setFillColor(sf::Color::Black);
    runText.setPosition(270,730);

    //Option2 text input
    char qualityInput;
    sf::Text qualityText("",font);
    qualityText.setPosition(1240, 355);
    sf::RectangleShape textbox(sf::Vector2f(100, 50));
    textbox.setFillColor(sf::Color::Transparent);
    textbox.setOutlineColor(sf::Color::White);
    textbox.setOutlineThickness(1);
    textbox.setPosition(1200, 350);

    //Option1 Result
    sf::Text result("", font);
    result.setPosition(1000, 600);

    //History Table
    queue<Record> history;
    sf::Text dataStruct("", font);
    dataStruct.setCharacterSize(25);
    sf::Text runTime("", font);
    sf::Text optionType("", font);
   
    while (window.isOpen()){
        
        window.clear();

        sf::Event event;
        while (window.pollEvent(event)){
            
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonReleased) {

                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    //option 1
                    if (mousePosition.y < 70 && mousePosition.y > 50 && mousePosition.x < 30 && mousePosition.x > 10) {
                        button1.setFillColor(sf::Color::White);
                        button2.setFillColor(sf::Color::Transparent);
                        result.setString("");
                    }
                    //option 2
                     if (mousePosition.y < 120 && mousePosition.y > 100 && mousePosition.x < 30 && mousePosition.x > 10) {
                        button1.setFillColor(sf::Color::Transparent);
                        button2.setFillColor(sf::Color::White);
                        result.setString("");
                     }
                        
                     //Card Selection
                     if (mousePosition.y > 100 && mousePosition.y < 500 && mousePosition.x > 820 && mousePosition.x < 1780 && button1.getFillColor() == sf::Color::White) {
                         short suit = (mousePosition.y - 100) / 100 + 1;
                         short rank = (mousePosition.x - 820) / 75 + 1;
                         
                         if (selectedCardsSet.find(make_pair(suit, rank)) == selectedCardsSet.end()) {
                             selectedCardsSet.insert(make_pair(suit, rank));
                             selectedCardsQueue.push(make_pair(suit, rank));
                         }
                         
                         if (selectedCardsSet.size() > 5) {
                             selectedCardsSet.erase(selectedCardsQueue.front());
                             selectedCardsQueue.pop();
                         }
                     }

                     //Run
                     if (mousePosition.y < 775 && mousePosition.y > 725 && mousePosition.x < 350 && mousePosition.x > 250) {
                         
                         if (button1.getFillColor() == sf::Color::White) { //Option 1
                             
                             if (selectedCardsSet.size() == 5) { //Selected hand size validation
                                 
                                 //convert selection to Hand
                                 vector<Card> hand;
                                 for (int i = 0; i < selectedCardsSet.size(); i++) {
                                     hand.push_back(Card(selectedCardsQueue.front().first, selectedCardsQueue.front().second));
                                     cout << selectedCardsQueue.front().first << "|" << selectedCardsQueue.front().second << endl;
                                     selectedCardsQueue.pop();
                                 }
                                 selectedCardsSet.clear();
                                 Hand temp = Hand(hand, -1); 
                                 
                                 //----Hash Map----
                                 //timer start
                                 auto start = std::chrono::high_resolution_clock::now();

                                 /*int quality = */hashMap->find(temp); //Hash Map find
                                
                                 //timer end
                                 auto stop = std::chrono::high_resolution_clock::now();

                                 auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                                 
                                 //Update History Table
                                 Record record = Record("Option 1", "Hash Map", duration.count());
                                 history.push(record);

                                 //----Tree Map----
                                 //timer start
                                 start = std::chrono::high_resolution_clock::now();

                                 int quality = treeMap->find(temp); //Hash Map find

                                 //timer end
                                 stop = std::chrono::high_resolution_clock::now();

                                 duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                                 
                                 //Update History Table
                                 record = Record("Option 2", "Tree Map", duration.count());
                                 history.push(record);
                                 
                                 //Output Result
                                 switch (quality){
                                 case 0:
                                     result.setString("The Selected hand is: Nothing in hand; not a recognized poker hand");
                                     break;
                                 case 1:
                                     result.setString("The Selected hand is: One pair; one pair of equal ranks within five cards");
                                     break;
                                 case 2:
                                     result.setString("Two pairs; two pairs of equal ranks within five cards");
                                     break;
                                 case 3:
                                     result.setString("The Selected hand is: Three of a kind; three equal ranks within five cards");
                                     break;
                                 case 4:
                                     result.setString("The Selected hand is: Straight; five cards, sequentially ranked with no gaps");
                                     break;
                                 case 5:
                                     result.setString("The Selected hand is: Flush; five cards with the same suit");
                                     break;
                                 case 6:
                                     result.setString("The Selected hand is: Full house; pair + different rank three of a kind");
                                     break;
                                 case 7:
                                     result.setString("The Selected hand is: Four of a kind; four equal ranks within five cards");
                                     break;
                                 case 8:
                                     result.setString("The Selected hand is: Straight flush; straight + flush");
                                     break;
                                 case 9:
                                     result.setString("The Selected hand is: Royal flush; {Ace, King, Queen, Jack, Ten} + flush");
                                     break;
                                 default:
                                     result.setString("The Selected hand is not in our dataset. :(");
                                     break;
                                 }
                                 
                             }
                             else { //If selection is < 5 cards
                                 result.setString("Please select a valid 5 card hand.");

                             }
                         }
                         if (button2.getFillColor() == sf::Color::White) {
                            if (isdigit(qualityInput)) { //Selected hand size validation

                                //----Hash Map----
                                //timer start
                                auto start = std::chrono::high_resolution_clock::now();

                                /*vector<Hand> hands = */hashMap->find((int)(qualityInput - '0')); //Hash Map find

                                //timer end
                                auto stop = std::chrono::high_resolution_clock::now();

                                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                                
                                //Update History Table
                                Record record = Record("Option 2", "Hash Map", duration.count());
                                history.push(record);

                                //----Tree Map----
                                //timer start
                                start = std::chrono::high_resolution_clock::now();

                                vector<Hand> hands = treeMap->find((int)(qualityInput - '0')); //Hash Map find

                                //timer end
                                stop = std::chrono::high_resolution_clock::now();

                                duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                                
                                //Update History Table
                                Record record2 = Record("Option 2", "Tree Map", duration.count());
                                history.push(record2);

                                //Display Found Hands
                                for (int h = 0; h < hands.size(); h++) {
                                    for (int c = 0; c < hands[h].cards.size(); c++) {
                                        cardImages[make_pair(hands[h].cards[c].suit, hands[h].cards[c].rank)].setPosition(820 + 75 * c + 6 * 75 * (h % 2), 100 * (h+1) % 2);
                                        window.draw(cardImages[make_pair(hands[h].cards[c].suit, hands[h].cards[c].rank)]);
                                    }
                                }

                            }
                            else { //If apha is entered instead of digit
                                result.setString("Please select a valid numeric quality (0-9).");
                            }
                         }
                     }
                    
                }
            }

            //Text input for option 2
            if (event.type == sf::Event::TextEntered && button2.getFillColor() == sf::Color::White)
            {
                qualityInput = event.text.unicode;
                qualityText.setString(qualityInput);
            }
        }
        
        
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
        window.draw(option1);
        window.draw(option2);
        window.draw(option);
        window.draw(runButton);
        window.draw(runText);

        //draw dynamic elements
        if(button1.getFillColor() == sf::Color::White) { //Option 1 only 
            
            //Draw All Cards
            for (int suit = 1; suit <= 4; suit++) {
                for (int rank = 1; rank <= 13; rank++) {
                    cardImages[make_pair(suit, rank)].setPosition(820 + 75 * (rank - 1), 100 * suit);
                    window.draw(cardImages[make_pair(suit, rank)]);
                }
            }

            //Outline Selected Cards
            for (auto cards : selectedCardsSet) {
                select.setPosition(820 + 75 * (cards.second - 1), 100 * cards.first);
                window.draw(select);
                //cout << 820 + 75 * (cards.second - 1) << " " << 100 * cards.first << endl;
            }
            
            //Display number of Chosen Cards out of 5
            string slash = "/";
            string slectionSize = to_string(selectedCardsSet.size());
            string five = "5";
            if (selectedCardsSet.size() != 5)
                numSelect.setFillColor(sf::Color::Red);
            else
                numSelect.setFillColor(sf::Color::Green);

            numSelect.setString(slectionSize+ slash + five);
            window.draw(numSelect);

        }
        else { //Option 2 Only
            window.draw(textbox);
            window.draw(qualityText);
        }
       
        //Display History Table Information
        queue<Record> temp(history);
        for (int i = 0; i < temp.size(); i++) {
            dataStruct.setString(temp.front().dataStruct);
            optionType.setString(temp.front().option);
            runTime.setString(to_string(temp.front().runTime));

            dataStruct.setPosition(530,110 + 30*i);
            optionType.setPosition(390,110 + 30*i);
            runTime.setPosition(715, 110 + 30*i);

            window.draw(dataStruct);
            window.draw(optionType);
            window.draw(runTime);
        }

        //Display result of Run
        window.draw(result);

        window.display();
    }

    return 0;
}