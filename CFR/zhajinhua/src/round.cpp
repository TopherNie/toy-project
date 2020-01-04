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
        player->id = PLAYER_0;
    } else{
        player->id = PLAYER_1;
    }
    playerList.push_back(player);
}

int Round::nextPlayer()
{
    currentPlayer = playerList.at((currentPlayer->id + 1) % playerList.size());
}

int Round::nextRoundStartPlayer()
{
    startPlayer = playerList.at((startPlayer->id + 1) % playerList.size());
}


int Round::preFlop()
{
    initCards(cards);

    dealCards(cards, playerList, PRE_FLOP);
    currentPlayer = startPlayer;

    // Small Blind
    auto* sbAction = new Action;
    sbAction->type = SMALL_BLIND;
    sbAction->bets = BASIC_BET;
    currentPlayer->history.push_back(sbAction);
    nextPlayer();

    // Big Blind
    auto* bbAction = new Action;
    bbAction->type = BIG_BLIND;
    int bbBets = BASIC_BET * 2;
    bbAction->bets = bbBets;
    lastUserBet = bbBets;
    currentPlayer->history.push_back(bbAction);
    nextPlayer();
}

int Round::settle(Player* winner)
{
    int winBets = 0;
    for (auto &p: playerList)
    {
        if (p != winner)
        {
            // Lose chips
            int loseChips = p->roundBets();
            p->totalChips -= loseChips;
            winBets += loseChips;
        }
    }
    // Win chips
    winner->totalChips += winBets;
}

int Round::battle()
{
    int playerSize = playerList.size();
    for (int s = FLOP; s <= TURN; s ++)
    {
        int i = 0;
        while (i < playerSize)
        {
            if (!currentPlayer->isOut)
            {
                Action* action = currentPlayer->play();
                if (action->type == FOLD)
                {
                    currentPlayer->isOut = true;
                } else if (action->type == CHECK)
                {
                    // Nothing to do
                }else if (action->type == CALL)
                {
                    action->bets = lastUserBet;
                } else if (action->type == RAISE)
                {
                    lastUserBet = action->bets;
                } else{
                    cout << "Wrong action type!" << endl;
                    continue;
                }
                currentPlayer->history.push_back(action);
                i ++;
            }
        }
        nextPlayer();
    }
}


int Round::clear()
{

}