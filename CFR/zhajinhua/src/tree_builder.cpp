//
// Created by Administrator on 2020/1/15 0015.
//


#include <tree_builder.h>
#include <algorithm>
#include <cmath>

int TreeBuilder::getNextPlayerID(int currentPlayerId)
{
    return inPlayerIDs.at((currentPlayerId + 1) % inPlayerIDs.size());
}

vector<Node<NodeVal*>*> TreeBuilder::getPlayChildren(NodeVal* parentVal)
{
    vector<Node<NodeVal*>*> children;

    int nextPlayerID = getNextPlayerID(parentVal->currentPlayerId);

    // Fold
    auto* foldVal = new NodeVal;
    foldVal->depth = parentVal->depth + 1;
    foldVal->type = NODE_TYPE_FOLD;
    foldVal->isTerminal = true;
    foldVal->currentPlayerId = nextPlayerID;
    foldVal->street = parentVal->street;
    foldVal->boardCards = parentVal->boardCards;
    auto* foldNode = new Node<NodeVal*>(foldVal);
    children.push_back(foldNode);

    // Check/call
    auto* callVal = new NodeVal;
    callVal->depth = parentVal->depth + 1;
    callVal->currentPlayerId = nextPlayerID;
    callVal->street = parentVal->street;
    callVal->boardCards = parentVal->boardCards;
    // Within a street
    callVal->type = NODE_TYPE_CALL;
    callVal->bet = parentVal->bet;
    if (!inPlayerIDs.empty() && inPlayerIDs.at(0) == nextPlayerID)
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
    array<int, 3> betSizeArr{0};
    transform(BET_RATE.begin(), BET_RATE.end(), betSizeArr.begin(), [parentVal](double x) { return (int)round(x * parentVal->pot);});
    for (auto &betSize: betSizeArr)
    {
        if (betSize > parentVal->bet)
        {
            auto* raiseVal = new NodeVal;
            raiseVal->depth = parentVal->depth + 1;
            raiseVal->currentPlayerId = nextPlayerID;
            raiseVal->street = parentVal->street;
            raiseVal->boardCards = parentVal->boardCards;
            raiseVal->type = NODE_TYPE_RAISE;
            raiseVal->bet = betSize;
        }
    }
}

void TreeBuilder::buildTreeR(Node<NodeVal*>* root)
{

}

void TreeBuilder::buildTree()
{

}
