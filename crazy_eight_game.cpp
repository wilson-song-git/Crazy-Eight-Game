
#include <iostream>
#include "card.h"
#include "player.h"
#include "deck.h"
#include <string>

using namespace std;

void dealHand(Deck &d, Player &p, int numCards) //deals 5 cards to each person's hand
{
    for (int i=0; i < numCards; i++)
        p.addCard(d.dealCard());
}
bool checkWin(int handSize) //check win function will determine if the player's hand is empty
{                            //and if it is empty then return true if not return false
    if (handSize == 0)
        return true;
    else
        return false;
}
void printSpaceLine()
{
    cout<<endl;
}



int main( )
{
    int numCards =5; // size of a hand
    Card firstCard; //will be the variable used for the first card that is dealed
    Card lastPile; //this is the variable that will hold the card that was entered last into play
    string playerEight;// when the player selects a crazy eight card this will be used to determine what suit they want
    char playerChoice; //choice that the player enters
    int asciiPlayerChoice; //changes between index and the letter choice that you choose
    Player p0("You");    // the person playing the game
    Player p1("Player 1");//player 1 - cpu
    Player p2("Player 2");//player 2 - cpu
    Player p3("Player 3");//player 3 - cpu
    
    bool win = false; //first declare that the wind condition is false
    bool hasCard;
    
    
    // create a deck of cards (shuffled).
    Deck d;
    
    // deal out cards to each player
    dealHand(d, p0, numCards);
    dealHand(d, p1, numCards);
    dealHand(d, p2, numCards);
    dealHand(d, p3, numCards);
    firstCard = d.dealCard(); //first card gets dealed
    lastPile=firstCard; //the last card in the pile first starts as the firstcard dealed
    //show hands of each player
    //cout << p1.getName() <<" has : " << p1.showHand() << endl;
    //cout << p2.getName() << " has : " << p2.showHand() << endl;
    
    
    //if decksize gets to zero its a draw
    // if win equals true exit loop too
    while (d.size() > 0 && win == false)
    {
        hasCard = false;
        
        
        //in this while, if player one has card with suit or
        //rank he plays it otherwise he draws another card
        
        while (!hasCard && d.size() > 0 && win == false)
        {
            //prints out the game interface for the player
            cout<<"Pile has "<<lastPile.toString()<<" <--- your turn"<<endl;
            printSpaceLine();
            cout<<" "<<p0.showHand()<<endl;
            
        beginChoice://for invalid responses go back here to start over
            printSpaceLine();
            cout<<"Which one to play?"<<endl;
            cin>>playerChoice;
            asciiPlayerChoice=int(playerChoice);
            
            //if you choose ? to cheat since ascii of ? is 63 then this will go through
            if(asciiPlayerChoice==63)// for ?
            {
                cout<<p1.getName()<<" "<<p1.showHand()<<endl;
                cout<<p2.getName()<<" "<<p2.showHand()<<endl;
                cout<<p3.getName()<<" "<<p3.showHand()<<endl;
                cout<<""<<endl;
            }
            
            //for if player enters like A,B,C instead of a,b,c
            if(asciiPlayerChoice<97&&asciiPlayerChoice>64)//if player enters uppercase-change to lower case
            {
                asciiPlayerChoice+=22;
            }
            
            //change the ascii to index so we can access the hand of the player class
            asciiPlayerChoice-=97;
            
            //the choice the choose cannot surpass the draw choice
            if(asciiPlayerChoice>p0.getHandSize())//makes sure that the player doesnt choose a choice that is not in range
            {
                cout<<"Your entered choice is invalid";
                goto beginChoice;
            }
            else{
                if(asciiPlayerChoice==p0.getHandSize())//this means that player has selected draw
                {
                    if (d.size() > 0) //if there is still cards in the deck draw
                    {
                        Card temp1 = d.dealCard();
                        p0.addCard(temp1);
                        cout<<"You have drawn a card."<<"Pile has "<<lastPile.toString()<<" <--- your turn"<<endl;
                        cout<<" "<<p0.showHand()<<endl;
                        goto beginChoice;
                    }
                }
                else if(!(asciiPlayerChoice==p0.getHandSize()))// if the player doesnt choose draw then it goes here
                {
                    if((p0.returnSpecificCard(asciiPlayerChoice).getRank())==8)//if the card is 8
                    {
                    beginSuit://to catch invalid responses go back here
                        cout<<"Which suit do you want?";
                        cin>>playerEight;
                        if(playerEight=="H"||playerEight=="h")
                        {
                            Card temp(0,Card::Hearts);//creates a temp card and then makes it the lastpile
                            lastPile=temp;
                        }
                        else if(playerEight=="S"||playerEight=="s")
                        {
                            Card temp(0,Card::Spades);
                            lastPile=temp;
                        }
                        else if(playerEight=="C"||playerEight=="c")
                        {
                            Card temp(0,Card::Clubs);
                            lastPile=temp;
                        }
                        else if(playerEight=="D"||playerEight=="d")
                        {
                            Card temp(0,Card::Diamonds);
                            lastPile=temp;
                        }
                        else//if the player entered none of the above choices then it is invalid and uses goto back up
                        {
                            cout<<"Invalid response please enter a suit!"<<endl;
                            goto beginSuit;
                        }
                        
                        //use returnSuitString() from card class to print the suit
                        cout<< "You have declared "<<lastPile.returnSuitString()<<endl;
                        cout<<"Pile has "<<lastPile.returnSuitString()<<"*"<<endl;
                        
                        hasCard=true;
                        
                    }
                    //if player choses a card with the matching rank then do this
                    else if(p0.returnSpecificCard(asciiPlayerChoice).getRank()==lastPile.getRank())
                    {
                        lastPile=p0.returnSpecificCard(asciiPlayerChoice);//makes the lastpile into the card that matched
                        p0.removeSpecificCard(asciiPlayerChoice);//removes the card
                        cout<<"Pile has "<<lastPile.toString()<<endl;
                        hasCard=true;
                    }
                    //if player chooses a card with the amtching suit then do this
                    else if(p0.returnSpecificCard(asciiPlayerChoice).getSuit()==lastPile.getSuit())
                    {
                        lastPile=p0.returnSpecificCard(asciiPlayerChoice);
                        p0.removeSpecificCard(asciiPlayerChoice);//removes the card
                        cout<<"Pile has "<<lastPile.toString()<<endl;
                        hasCard=true;
                    }
                }
                else
                {
                    //this catches if the player didnt pick a valid letter choice
                    cout<<""<<endl;
                    cout<<"!!!Your choice is invalid and cannot be played. Please try again.!!!"<<endl;
                    goto beginChoice;
                }
            }
            
        }
        hasCard = false;
        
        //check if player one won in that above while loop
        //if so we skip this next loop and end game
        if (checkWin(p0.getHandSize()))
            win = true;
        
        //same as above while loop except for with player 1
        while (!hasCard && d.size() > 0 && win == false)
        {
            
            if (p1.hasCardWithRank(lastPile.getRank(), lastPile))
            {
                p1.removeCardFromHand(lastPile);
                cout << "  "<<p1.getName() << " chose " << lastPile.toString() << endl;
                
                if(lastPile.getRank()==8)
                {
                    cout<<p1.getName()<<" chose"<<lastPile.toString()<<endl;
                    cout<<p1.getName()<<" has declared "<<p1.mostOccur()<<endl;
                    cout<<"Pile has "<<p1.mostOccur()<<"*"<<endl;
                    if(p1.mostOccur()=="H")
                    {
                        Card temp(0,Card::Hearts);
                        lastPile=temp;
                    }
                    else if(p1.mostOccur()=="S")
                    {
                        Card temp(0,Card::Spades);
                        lastPile=temp;
                    }
                    else if(p1.mostOccur()=="C")
                    {
                        Card temp(0,Card::Clubs);
                        lastPile=temp;
                    }
                    else if(p1.mostOccur()=="D")
                    {
                        Card temp(0,Card::Diamonds);
                        lastPile=temp;
                    }
                }
                else{
                    cout<<" "<<p1.getName()<<" chose "<<lastPile.toString()<<endl;
                    cout<<"Pile has "<<lastPile.toString()<<endl;
                }
                hasCard = true;
            }
            else if (p1.hasCardWithSuit(lastPile.getSuit(), lastPile))
            {
                p1.removeCardFromHand(lastPile);
                if(lastPile.getRank()==8)
                {
                    cout<<p1.getName()<<" chose"<<lastPile.toString()<<endl;
                    cout<<p1.getName()<<" has declared "<<p1.mostOccur()<<endl;
                    cout<<"Pile has "<<p1.mostOccur()<<"*"<<endl;
                    if(p1.mostOccur()=="H")
                    {
                        Card temp(0,Card::Hearts);
                        lastPile=temp;
                    }
                    else if(p1.mostOccur()=="S")
                    {
                        Card temp(0,Card::Spades);
                        lastPile=temp;
                    }
                    else if(p1.mostOccur()=="C")
                    {
                        Card temp(0,Card::Clubs);
                        lastPile=temp;
                    }
                    else if(p1.mostOccur()=="D")
                    {
                        Card temp(0,Card::Diamonds);
                        lastPile=temp;
                    }
                }
                else
                {
                    cout << "  "<<p1.getName() << " chose " << lastPile.toString() << endl;
                    cout<<"Pile has "<<lastPile.toString()<<endl;
                    hasCard = true;
                }
            }
            else
            {
                if (d.size() > 0) //if there is still cards in the deck draw
                {
                    Card temp = d.dealCard();
                    p1.addCard(temp);
                    cout << "  "<<p1.getName() << " drawing..."<<endl;
                }
            }
        }
        hasCard = false;
        
        if (checkWin(p1.getHandSize()))
            win = true;
        
        //same as above while loop except for with player 2
        while (!hasCard && d.size() > 0 && win == false)
        {
            
            if (p2.hasCardWithRank(lastPile.getRank(), lastPile))
            {
                p2.removeCardFromHand(lastPile);
                cout << "  "<<p2.getName() << " chose " << lastPile.toString() << endl;
                if(lastPile.getRank()==8)
                {
                    cout<<p2.getName()<<" chose "<<lastPile.toString()<<endl;
                    cout<<p2.getName()<<" has declared "<<p2.mostOccur()<<endl;
                    cout<<"Pile has "<<p2.mostOccur()<<"*"<<endl;
                    if(p2.mostOccur()=="H")
                    {
                        Card temp(0,Card::Hearts);
                        lastPile=temp;
                    }
                    else if(p2.mostOccur()=="S")
                    {
                        Card temp(0,Card::Spades);
                        lastPile=temp;
                    }
                    else if(p2.mostOccur()=="C")
                    {
                        Card temp(0,Card::Clubs);
                        lastPile=temp;
                    }
                    else if(p2.mostOccur()=="D")
                    {
                        Card temp(0,Card::Diamonds);
                        lastPile=temp;
                    }
                }
                
                else
                {
                    cout<<p2.getName()<<" chose "<<lastPile.toString()<<endl;
                    cout<<"Pile has "<<lastPile.toString()<<endl;
                }
                
                hasCard = true;
            }
            
            else if (p2.hasCardWithSuit(lastPile.getSuit(), lastPile))
            {
                p2.removeCardFromHand(lastPile);
                
                if(lastPile.getRank()==8)
                {
                    cout<<p2.getName()<<" chose "<<lastPile.toString()<<endl;
                    cout<<p2.getName()<<" has declared "<<p2.mostOccur()<<endl;
                    cout<<"Pile has "<<p2.mostOccur()<<"*"<<endl;
                    if(p2.mostOccur()=="H")
                    {
                        Card temp(0,Card::Hearts);
                        lastPile=temp;
                    }
                    else if(p2.mostOccur()=="S")
                    {
                        Card temp(0,Card::Spades);
                        lastPile=temp;
                    }
                    else if(p2.mostOccur()=="C")
                    {
                        Card temp(0,Card::Clubs);
                        lastPile=temp;
                    }
                    else if(p2.mostOccur()=="D")
                    {
                        Card temp(0,Card::Diamonds);
                        lastPile=temp;
                    }
                    
                }
                else
                {
                    cout << "  "<<p2.getName() << " chose " << lastPile.toString() << endl;
                    cout<<"Pile has "<<lastPile.toString()<<endl;
                    
                }
                hasCard=true;
            }
            else
            {
                if (d.size() > 0) //if there is still cards in the deck draw
                {
                    Card temp = d.dealCard();
                    p2.addCard(temp);
                    cout << "  "<<p2.getName() << " drawing..."<<endl;
                }
            }
        }
        hasCard = false;
        
        if (checkWin(p2.getHandSize()))
            win = true;
        //same as above while loop except for with player 3
        while (!hasCard && d.size() > 0 && win == false)
        {
            
            if (p3.hasCardWithRank(lastPile.getRank(), lastPile))
            {
                p3.removeCardFromHand(lastPile);
                if(lastPile.getRank()==8)
                {
                    cout<<p3.getName()<<" chose"<<lastPile.toString()<<endl;
                    cout<<p3.getName()<<" has declared "<<p3.mostOccur()<<endl;
                    cout<<"Pile has "<<p3.mostOccur()<<"*"<<endl;
                    if(p3.mostOccur()=="H")
                    {
                        Card temp(0,Card::Hearts);
                        lastPile=temp;
                    }
                    else if(p3.mostOccur()=="S")
                    {
                        Card temp(0,Card::Spades);
                        lastPile=temp;
                    }
                    else if(p3.mostOccur()=="C")
                    {
                        Card temp(0,Card::Clubs);
                        lastPile=temp;
                    }
                    else if(p3.mostOccur()=="D")
                    {
                        Card temp(0,Card::Diamonds);
                        lastPile=temp;
                    }
                }
                else
                {
                    cout<<p3.getName()<<" chose "<<lastPile.toString()<<endl;
                    cout<<"Pile has "<<lastPile.toString()<<endl;
                }
                hasCard = true;
            }
            else if (p3.hasCardWithSuit(lastPile.getSuit(), lastPile))
            {
                if(lastPile.getRank()==8)
                {
                    cout<<p3.getName()<<" chose "<<lastPile.toString()<<endl;
                    cout<<p3.getName()<<" has declared "<<p3.mostOccur()<<endl;
                    cout<<"Pile has "<<p3.mostOccur()<<"*"<<endl;
                    if(p3.mostOccur()=="H")
                    {
                        Card temp(0,Card::Hearts);
                        lastPile=temp;
                    }
                    else if(p3.mostOccur()=="S")
                    {
                        Card temp(0,Card::Spades);
                        lastPile=temp;
                    }
                    else if(p3.mostOccur()=="C")
                    {
                        Card temp(0,Card::Clubs);
                        lastPile=temp;
                    }
                    else if(p3.mostOccur()=="D")
                    {
                        Card temp(0,Card::Diamonds);
                        lastPile=temp;
                    }
                }
                else
                {
                    p3.removeCardFromHand(lastPile);
                    cout << "  "<<p3.getName() << " chose " << lastPile.toString() << endl;
                    
                }
                hasCard=true;
            }
            else
            {
                if (d.size() > 0) //if there is still cards in the deck draw
                {
                    Card temp = d.dealCard();
                    p3.addCard(temp);
                    cout << "  "<<p3.getName() << " drawing..."<<endl;
                }
            }
        }
        hasCard = false;
        
        if (checkWin(p3.getHandSize()))
            win = true;
    }
    
    
    //print out who won
    cout << "game over \n";
    if (d.size() == 0)
        cout << "its a draw! " << endl;
    else if (checkWin(p0.getHandSize()))
        cout << p0.getName() << " wins!" << endl;
    else if (checkWin(p1.getHandSize()))
        cout << p1.getName() << " wins !" << endl;
    else if (checkWin(p2.getHandSize()))
        cout << p2.getName() << " wins !" << endl;
    else if (checkWin(p3.getHandSize()))
        cout << p3.getName() << " wins !" << endl;
    
    system("pause");
    return 0;
}






