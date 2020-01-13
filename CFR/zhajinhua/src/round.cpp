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

State* Round::buildState(int currentStreet)
{
    auto* state = new State;
    state->boardCards = boardCards;
    state->streetActionMap = streetActionMap;
    state->pot = pot;
    state->currentStreet = currentStreet;
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
        if (!streetActionMap.count(s))
        {
            vector<pair<int, Action*>> actionOfUsers;
            streetActionMap[s] = actionOfUsers;
        }
        int i = 0;
        while (i < playerSize)
        {
            if (!currentPlayer->isOut)
            {
                State* state = buildState(s);
                Action* action = currentPlayer->play(state);
                if (action->type == FOLD)
                {
                    currentPlayer->isOut = true;
                    if (inPlayerNum() <= 1)
                    {
                        return;
                    }
                } else if (action->type == CHECK){
                    // Can check only if the first player of the current street checked
                    if (!streetActionMap[s].empty() && streetActionMap[s].at(0).second->type == RAISE)
                    {
                        cout << "Cannot check because the street's first player raised." << endl;
                        continue;
                    }
                } else if (action->type == CALL){
                    if (i == 0)
                    {
                        cout << "You are the first player of the street. Don't call. Raise or check instead." << endl;
                        continue;
                    }
                    action->bets = lastBet;
                } else if (action->type == RAISE && action->bets > 0){
                    lastBet = action->bets;
                } else{
                    cout << "Wrong action type!" << endl;
                    continue;
                }
                currentPlayer->history.push_back(action);
                streetActionMap[s].emplace_back(currentPlayer->id, action);
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
    int winBets = 0;

    cout << "Losers: ";
    for (auto &p: playerList)
    {
        // Losers
        if (count(winnerList.begin(), winnerList.end(), p) == 0)
        {
            if (p->isOut)
            {
                p->cardsType = TYPE_FOLD;
            }
            // Lose chips
            int loseChips = p->getRoundBets();
            p->totalChips -= loseChips;
            winBets += loseChips;
            cout << p->name << "(" << TYPE_MAP.at(p->cardsType) << " | " << vecToString(p->cards) << " | -" << loseChips << " Chips" << "); ";
        }
    }
    if (winBets == 0)
    {
        cout << "None";
    }
    cout << endl;

    int winnerCount = winnerList.size();
    int winBetsPerWinner = winBets / winnerCount;

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
        cout << winner->name << "(" << TYPE_MAP.at(winner->cardsType) << " | " << vecToString(winner->cards) << " | +" << winBetsPerWinner << " Chips" << "); ";
    }
    cout << endl;
}

void Round::clear()
{
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
    pot = 0;
    boardCards.clear();
    streetActionMap.clear();
    nextRoundStartPlayer();
    cout << "Round " << serial << " finish!" << endl;
    cout << "======================================================" << endl;
    for (auto &p: playerList)
    {
        p->confirmToContinue();
    }
    cout << "======================================================" << endl;
}

void Round::run()
{
    while (serial < roundNum)
    {
        prepare();
        battle();
        settle();
        clear();
        serial ++;
    }
}