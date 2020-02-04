
#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>
#include <string>
#include <vector>

#include "card.h"
using namespace std;


class Player
{
  public:
    Player();

    Player(string n) {
        name = n;
    }

    string getName() const {
       return name;
    }

    string showHand(); //returns a string with all the cards in their hand

   int getHandSize() const;

    void addCard(Card c);              //adds a card to the hand

    //Remove the card c from the hand and return true if successful
   bool removeCardFromHand(Card c);

    //Does the player have a card with the given rank in her hand?
    //e.g. a call to a player with a 7d would return true and set c1 to 7d
    //  if passed a 7 as a parameter.  Otherwise returns false
    bool hasCardWithRank(int r, Card &c1);

    //Does the player have a card with the given Suit in her hand?
    //Similar to hasCardWithSuit
    bool hasCardWithSuit(Card::Suit s, Card &c1);

    //returns the index of the last card to use to check if player goes past
    int returnLastCard();

    //used to remove a specific card at a certain index in the hand
    void removeSpecificCard(int l);

    //used to return a specific card at a certain index
    Card returnSpecificCard(int c);

    string mostOccur();

  private:

    vector <Card> hand;  // VECTOR

    string name;

    //int lastCard;

};

#endif


