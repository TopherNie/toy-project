//
// Created by Administrator on 2020/1/15 0015.
//


#include <tree_builder.h>

static vector<Node<NodeVal*>*> getPlayChildren(NodeVal* parentVal)
{
    vector<Node<NodeVal*>*> children;

    // Fold
    auto* foldVal = new NodeVal;
    foldVal->type = FOLD;
    foldVal->isTerminal = true;
    foldVal->currentPlayerId = parentVal->nextPlayerId;
    foldVal->street = parentVal->street;
    foldVal->boardCards = parentVal->boardCards;
    auto* foldNode = new Node<NodeVal*>(foldVal);
    children.push_back(foldNode);

    // Check/call within a street


}

static void buildTreeR(Node<NodeVal*>* root)
{

}

void buildTree()
{

}

