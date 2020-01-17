//
// Created by Administrator on 2020/1/15 0015.
//


#include <tree_builder.h>

int TreeBuilder::getNextPlayerID(int currentPlayerId)
{
    return inPlayersId.at((currentPlayerId + 1) % inPlayersId.size());
}

vector<Node<NodeVal*>*> TreeBuilder::getPlayChildren(NodeVal* parentVal)
{
    vector<Node<NodeVal*>*> children;

    int nextPlayerID = getNextPlayerID(parentVal->currentPlayerId);

    // Fold
    auto* foldVal = new NodeVal;
    foldVal->type = NODE_TYPE_FOLD;
    foldVal->isTerminal = true;
    foldVal->currentPlayerId = nextPlayerID;
    foldVal->street = parentVal->street;
    foldVal->boardCards = parentVal->boardCards;
    auto* foldNode = new Node<NodeVal*>(foldVal);
    children.push_back(foldNode);

    // Check/call
    auto* callVal = new NodeVal;
    callVal->currentPlayerId = nextPlayerID;
    callVal->street = parentVal->street;
    callVal->boardCards = parentVal->boardCards;
    // Within a street
    callVal->type = NODE_TYPE_CALL;
    // Transition


    // Terminal
    auto* callNode = new Node<NodeVal*>(callVal);
    children.push_back(callNode);

    // Bet

}

void TreeBuilder::buildTreeR(Node<NodeVal*>* root)
{

}

void TreeBuilder::buildTree()
{

}
