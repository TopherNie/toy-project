//
// Created by Administrator on 2019/12/28 0028.
//

#include <iostream>
#include <round.h>
#include <algorithm>
#include <tools.h>

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

void Round::addPlayer(Player * player)
{
    int playerNum = playerList.size();
    if (playerNum >= 2)
    {
        cout << "The number of player cannot be more than 2" << endl;
        return ;
    }
    player->id = playerNum;
    playerList.push_back(player);
}

void Round::nextPlayer()
{
    do{
        currentPlayer = playerList.at((currentPlayer->id + 1) % playerList.size());
    }while (currentPlayer->isOut);
}

void Round::nextRoundStartPlayer()
{
    startPlayer = playerList.at((startPlayer->id + 1) % playerList.size());
}


void Round::prepare()
{
    cout << "Round " << serial << " begins!" << endl;
    initCards(allCards);

    dealHoleCards(allCards, playerList);

    if (startPlayer == nullptr)
    {
        startPlayer = playerList.at(0);
    }
    currentPlayer = startPlayer;

    // Small Blind
    auto* sbAction = new Action;
    sbAction->type = SMALL_BLIND;
    sbAction->bets = BASIC_BET;
    pot += sbAction->bets;
    currentPlayer->history.push_back(sbAction);
    nextPlayer();

    // Big Blind
    auto* bbAction = new Action;
    bbAction->type = BIG_BLIND;
    int bbBets = BASIC_BET * 2;
    bbAction->bets = bbBets;
    pot += bbAction->bets;
    lastBet = bbBets;
    currentPlayer->history.push_back(bbAction);
    nextPlayer();
}

Node* Round::buildNode()
{
    Node* node = new Node;
    node->board = boardCards;
}

void Round::battle()
{
    int playerSize = playerList.size();
    // Street
    int s = PRE_FLOP;

    while (s <= TURN)
    {
        if (s != PRE_FLOP)
        {
            dealPublicCard(allCards, boardCards);
        }
        int i = 0;
        while (i < playerSize)
        {
            if (!currentPlayer->isOut)
            {
                // Information board for human player
                if (!currentPlayer->isRobot())
                {
                    cout << "Your hole cards: " << vecToString(currentPlayer->cards) << " || Board: " << vecToString(boardCards)
                            << " || Pot: " << pot << " || Round last bet: " << lastBet << endl;
                }
                Action* action = currentPlayer->play();
                if (action->type == FOLD)
                {
                    currentPlayer->isOut = true;
                    if (inPlayerNum() <= 1)
                    {
                        return;
                    }
                } else if (action->type == CHECK){
                    // Nothing to do
                } else if (action->type == CALL && action->bets > 0){
                    action->bets = lastBet;
                } else if (action->type == RAISE){
                    lastBet = action->bets;
                } else{
                    cout << "Wrong action type!" << endl;
                    continue;
                }
                currentPlayer->history.push_back(action);
                pot += action->bets;
                cout << currentPlayer->name << "'s action: " << action->toString() << endl;
                cout << "--------------------------------------------------------------------" << endl;

            }
            nextPlayer();
            if (s == TURN && i == playerSize - 1)
            {
                return;
            }
            i ++;
        }
        s ++;
    }
}


void Round::settle()
{
    vector<Player*> winnerList;
    if (inPlayerNum() == 1)
    {
        // All players have folded except the winner.
        winnerList.push_back(inPlayers().at(0));
    } else{
        winnerList = findWinnerByCard(playerList, boardCards);
    }
    unsigned int winBets = 0;

    cout << "Losers: ";
    for (auto &p: playerList)
    {
        // Losers
        if (count(winnerList.begin(), winnerList.end(), p) == 0)
        {
            // Lose chips
            int loseChips = p->getRoundBets();
            p->totalChips -= loseChips;
            winBets += loseChips;
            cout << p->name << "(" << TYPE_MAP[p->cardsType] << " | " << vecToString(p->cards) << " | -" << loseChips << " Chips" << "); ";
        }
    }
    if (winBets == 0)
    {
        cout << "None";
    }
    cout << endl;

    unsigned int winnerCount = winnerList.size();
    unsigned int winBetsPerWinner = winBets / winnerCount;

    if (winBets == 0)
    {
        cout << "Draw: ";
    } else{
        cout << "Winners: ";
    }
    for (auto &winner: winnerList)
    {
        // Win chips
        winner->totalChips += winBetsPerWinner;
        cout << winner->name << "(" << TYPE_MAP[winner->cardsType] << " | " << vecToString(winner->cards) << " | +" << winBetsPerWinner << " Chips" << "); ";
    }
    cout << endl;
}

void Round::clear()
{
    pot = 0;
    boardCards.clear();
    for (auto &p: playerList)
    {
        p->cards.clear();
        p->cardsType = SINGLE;
        p->cardTypeIndexes.clear();
        p->isOut = false;
        int actionCount = p->history.size();
        for (int i = 0; i < actionCount; i ++)
        {
            delete(p->history.at(i));
        }
        p->history.clear();
    }
    nextRoundStartPlayer();
    cout << "Round " << serial << " finish!" << endl;
    cout << "======================================================" << endl;
    cout << "======================================================" << endl;
    serial ++;
}