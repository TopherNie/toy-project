//
// Created by Administrator on 2020/1/15 0015.
//


#include <tree_builder.h>

static vector<Node<NodeVal*>*> getChildren(NodeVal* parentVal)
{
    vector<Node<NodeVal*>*> children;

    // Fold
    auto* foldVal = new NodeVal;
    foldVal->type = NODE_TYPE_TERMINAL_FOLD;
    foldVal->isTerminal = true;
    foldVal->currentPlayerId = parentVal->nextPlayerId;
    foldVal->street = parentVal->street;
    foldVal->boardCards = parentVal->boardCards;
    auto* foldNode = new Node<NodeVal*>(foldVal);
    children.push_back(foldNode);

    //
}

static void buildTreeR(Node<NodeVal*>* root)
{

}

void buildTree()
{

}

