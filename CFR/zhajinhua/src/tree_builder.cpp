//
// Created by Administrator on 2020/1/15 0015.
//


#include <tree_builder.h>
#include <algorithm>
#include <cmath>
#include <zjh_utils.h>

PlayerNodeInfo* TreeBuilder::getNextPlayerInfo(int currentPlayerId, const vector<PlayerNodeInfo*>& playerNodeInfoVec)
{
    return playerNodeInfoVec.at((currentPlayerId + 1) % playerNodeInfoVec.size());
}

vector<Node<NodeVal*>*> TreeBuilder::getPlayChildren(NodeVal* parentVal)
{
    vector<Node<NodeVal*>*> children;
    if (parentVal->isTerminal || parentVal->isTransitional)
    {
        return children;
    }

    PlayerNodeInfo* nextPlayerInfo = getNextPlayerInfo(parentVal->currentPlayerId, parentVal->playerNodeInfoVec);

    // Fold
    auto* foldVal = new NodeVal;
    foldVal->depth = parentVal->depth + 1;
    foldVal->type = NODE_TYPE_FOLD;
    foldVal->isTerminal = true;
    foldVal->currentPlayerId = nextPlayerInfo->playerID;
    foldVal->street = parentVal->street;
    foldVal->boardCards = parentVal->boardCards;
    auto* foldNode = new Node<NodeVal*>(foldVal);
    children.push_back(foldNode);

    // Check/call
    auto* callVal = new NodeVal;
    callVal->depth = parentVal->depth + 1;
    callVal->currentPlayerId = nextPlayerInfo->playerID;
    callVal->street = parentVal->street;
    callVal->boardCards = parentVal->boardCards;
    // Within a street
    callVal->type = NODE_TYPE_CALL;
    callVal->bet = parentVal->bet;
    callVal->pot = parentVal->pot + callVal->bet;
    callVal->playerNodeInfoVec = parentVal->playerNodeInfoVec;
    callVal->playerNodeInfoVec.at(callVal->currentPlayerId)->roundBet += callVal->bet;

    if (nextPlayerInfo->playerID == parentVal->playerNodeInfoVec.at(0)->playerID)
    {
        if (parentVal->street == TURN)
        {
            // Terminal
            callVal->isTerminal = true;
        } else{
            // Transition
            callVal->isTransitional = true;
        }
    }
    auto* callNode = new Node<NodeVal*>(callVal);
    children.push_back(callNode);

    // Bet
    vector<int> betSizeStrVec = getBetSizeVec(nextPlayerInfo->roundBet, parentVal->pot, parentVal->bet);
    for (auto &betSize: betSizeStrVec)
    {
        if (betSize > parentVal->bet)
        {
            auto* raiseVal = new NodeVal;
            raiseVal->depth = parentVal->depth + 1;
            raiseVal->currentPlayerId = nextPlayerInfo->playerID;
            raiseVal->street = parentVal->street;
            raiseVal->boardCards = parentVal->boardCards;
            raiseVal->type = NODE_TYPE_RAISE;
            raiseVal->bet = betSize;
            raiseVal->pot = parentVal->pot + betSize;
            raiseVal->playerNodeInfoVec = parentVal->playerNodeInfoVec;
            raiseVal->playerNodeInfoVec.at(raiseVal->currentPlayerId)->roundBet += betSize;
            auto* raiseNode = new Node<NodeVal*>(raiseVal);
            children.push_back(raiseNode);
        }
    }
    return children;
}

void TreeBuilder::buildTreeR(Node<NodeVal*>* root)
{
    vector<Node<NodeVal*>*> children = getPlayChildren(root->_val);
    root->_children = children;
    for (auto* child: children)
    {
        buildTreeR(child);
    }
}

