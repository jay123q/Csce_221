#include <string>
#include <iostream>
#include <sstream>

#include "Card.h"
using namespace std;

int rand221(void) {
    return rand();
}

// You may want to write the following three functions, but they are not required

std::istream& operator>>(std::istream& in, Suit& suit) 
{
    string Line;
    in >> Line;
    if(Line == "spades")
    {
        suit = Suit::SPADES;
    }
    else if(Line == "diamonds")
    {
        suit = Suit::DIAMONDS;
    }
    else if(Line == "clubs")
    {
        suit = Suit::CLUBS;
    }
    else if(Line == "hearts")
    {
        suit = Suit::HEARTS;

    }
    else{in.clear(std::ios_base::failbit);}
    return in;

    
}

Rank to_rank(const std::string& string) {

 
        if(string == "ace"){ return 1; }
        else if(string == "jack") { return 11; }
        else if(string == "queen"){ return 12; }
        else if(string == "king"){ return 13; }
        else{ 
           // try{
                int Box = stoi(string);
               // std::cout << "string " << string << std::endl;
                return Box;
              //  }catch(std::invalid_argument){} 
            }
    
        
}

std::istream& operator>>(std::istream& in, Card& card) 
{
 
    string RankString;
    in>>card.suit;
    in>>RankString;
    card.rank=to_rank(RankString);
    cout << "Read in " << RankString << endl;
    return in;

}

List<Card> buildDeck(std::istream& file) {
    // TODO
    Card Box;
    string Holder;

    List <Card> store;

    while(getline(file,Holder))
    {  
        if(Holder.empty()){break;}
        stringstream ss(Holder);
        ss>>Box;
        if(ss.fail())
        {break;}
        store.push_back(Box);
    }
    // for(int i = 0 ; i < 12 ; i++)
    // {
    //     file>>Box;
    //     store.push_back(Box);
    // }
    return store;
}

List<Card> shuffle(const List<Card>& deck) {
    // TODO
    List<Card> DeckShuffle;
    int RandomValue=0; 
    // coin flipper
  //  bool CheckDoubleValue = false;
    for(const auto & i : deck)
    {
        RandomValue = rand221();
        if(RandomValue%2)
        {
            DeckShuffle.push_back(i);

        }
        else
        {
            DeckShuffle.push_front(i);
 
        }
    }
    return DeckShuffle;
}