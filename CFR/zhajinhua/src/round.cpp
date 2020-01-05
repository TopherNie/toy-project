//
// Created by Administrator on 2019/12/28 0028.
//

#include <iostream>
#include <round.h>

using namespace std;

vector<Player*> Round::inPlayers()
{
    vector<Player*> vec;
    for (auto &p: playerList)
    {
        if (!p->isOut)
        {
            vec.push_back(p);
        }
    }
    return vec;
}

int Round::inPlayerNum()
{
    int num = 0;
    for (auto &p: playerList)
    {
        if (!p->isOut)
        {
            num ++;
        }
    }
    return num;
}

int Round::addPlayer(Player * player)
{
    int playerNum = playerList.size();
    if (playerNum >= 2)
    {
        cout << "The number of player cannot be more than 2" << endl;
        return -1;
    }
    player->id = playerNum;
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
    initCards(allCards);

    dealHoleCards(allCards, playerList);
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

int Round::settle()
{
    Player* winner;
    if (inPlayerNum() == 1)
    {
        winner = inPlayers().at(0);
    } else{
        winner = findWinnerByCard(playerList, boardCards);
    }
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
    // Street
    int s = FLOP;

    while (s <= TURN)
    {
        dealPublicCard(allCards, boardCards);
        int i = 0;
        while (i < playerSize)
        {
            if (!currentPlayer->isOut)
            {
                // Information board for human player
                if (!currentPlayer->isRobot)
                {
                    cout << "" << endl;
                }
                Action* action = currentPlayer->play();
                if (action->type == FOLD)
                {
                    currentPlayer->isOut = true;
                    if (inPlayerNum() <= 1)
                    {
                        return 0;
                    }
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
            if (s == TURN && i == playerSize - 1)
            {
                return 0;
            }
            nextPlayer();
        }
        s ++;
    }
}


int Round::clear()
{

}