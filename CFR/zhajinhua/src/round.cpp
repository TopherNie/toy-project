//
// Created by Administrator on 2019/12/28 0028.
//

#include <iostream>
#include <round.h>

using namespace std;

int Round::addPlayer(Player * player)
{
    int playerNum = playerList.size();
    if (playerNum >= 2)
    {
        cout << "The number of player cannot be more than 2" << endl;
        return -1;
    }
    if (playerNum == 0)
    {
        player -> id = PLAYER_0;
    } else{
        player -> id = PLAYER_1;
    }
    playerList.push_back(player);
}

int Round::nextPlayer()
{
    currentPlayer = (currentPlayer + 1) % playerList.size();
}

int Round::preFlop()
{
    initCards(cards);
    currentPlayer = serial % 2 == 0 ? PLAYER_0 : PLAYER_1;
    dealCards(cards, playerList, PRE_FLOP);
    // Blind bet
    for (auto &p: playerList)
    {
        string action;
        if (p -> id == currentPlayer)
        {
            // Small Blind
            action.append(SMALL_BLIND).append(to_string(BASIC_BET));
        } else{
            // Big Blind
            action.append(BIG_BLIND).append(to_string(BASIC_BET * 2)) ;
        }
        p -> history.push_back(action);
    }
}

int Round::battle()
{
    for (int s = FLOP; s <= TURN; s ++)
    {
        for (auto &p: playerList)
        {
            p->play();
        }
    }
}

int Round::clear()
{

}