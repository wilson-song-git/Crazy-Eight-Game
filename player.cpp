#include "player.h"

Player::Player()
{
	name = "blank";

}
//show the hand a player has
string Player::showHand()
{
	string s;
	int count=0;
	//create a string of all the cards in
	//players hand
	for (int i = 0; i < hand.size(); i++)
	{
		s += "(";
		s += char(97+i);
		s += ")";
		s += " ";
		s += hand[i].toString();
		s += " ";
		count++;

	}
	s+="(";
	s+=char(97+count);
	s+=")";
	s+=" draw";
	s+=" ";
	return s;
}
/*
int Player::returnLastCard()
{
	return lastCard;
}*/

//return hand size
int Player::getHandSize() const
{
	return hand.size();
}
//add card to the hand
void Player::addCard(Card c)
{

	hand.push_back(c);
}
// find out if player can play a card of same rank
bool Player::hasCardWithRank(int r, Card &c1)
{
	bool match = false;
	for (int i = 0; i < hand.size() && match == false; i++)
	{
		if (hand[i].getRank() == r)
		{
			match = true;
			c1 = hand[i];
		}
	}
	return match;
}
//find out if player has a card of same suuit to play
bool Player::hasCardWithSuit(Card::Suit s, Card &c1)
{
	bool match = false;
	for (int i = 0; i < hand.size() && match == false; i++)
	{
		if (hand[i].getSuit() == s || hand[i].getRank() == 8)
		{
			match = true;
			c1 = hand[i];
		}
	}
	return match;
}

//player plays card
bool Player::removeCardFromHand(Card c)
{
	for (int i = 0; i < hand.size(); i++)
	{
		if (c == hand[i])
		{
			hand.erase(hand.begin() + i);
			return true;
		}
	}
	return false;
}

void Player::removeSpecificCard(int l)
{
	hand.erase(hand.begin() + l);
}

Card Player::returnSpecificCard(int c)
{
	return hand[c];
}

string Player::mostOccur()
{
	int heartCount=0;
	int spadeCount=0;
	int clubCount=0;
	int diamondCount=0;
	int max=heartCount;
	string result="H";
	for (int i = 0; i < hand.size(); i++)
	{
		if(hand[i].getSuit()==Card::Hearts)
			heartCount++;
		if(hand[i].getSuit()==Card::Spades)
				spadeCount++;
		if(hand[i].getSuit()==Card::Clubs)
				clubCount++;
		if(hand[i].getSuit()==Card::Diamonds)
				diamondCount++;
	}
	if(spadeCount>max)
	{
		max=spadeCount;
		result="S";
	}
	if(clubCount>max)
	{
		max=clubCount;
		result="C";
	}
	if(diamondCount>max)
	{
		max=diamondCount;
		result="D";
	}

	return result;

}

