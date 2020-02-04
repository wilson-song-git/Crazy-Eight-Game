
#ifndef _CARD_H
#define _CARD_H


#include <iostream>
#include <string>
using namespace std;

class Card
{
  public:

    enum Suit {Spades, Hearts, Diamonds, Clubs};

    Card();                     // default: ace of spades

    Card(int, Suit);

    string toString();  // return string version: Ac 4h Js
    int   getRank() const;  // return rank, 1..13
    string returnRankString();
    Suit  getSuit() const;  // return suit
    string returnSuitString();
    void setSuit();

    bool operator == (const Card &rhs);

  private:

    int rank;
    Suit suit;

    string suitString(); // return "s", "h",...
    string rankString();// return "A", "2", ..."Q"*/

};

#endif
