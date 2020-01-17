//
// Created by Administrator on 2020/1/15 0015.
//

#ifndef TOY_PROJECT_TREE_BUILDER_H
#define TOY_PROJECT_TREE_BUILDER_H

#include <tree.h>
#include <state.h>
#include <constants.h>

class TreeBuilder
{
private:
    int getNextPlayerID(int currentPlayerId);
    vector<Node<NodeVal*>*> getPlayChildren(NodeVal* parentVal);
    void buildTreeR(Node<NodeVal*>* root);

public:
    vector<int> inPlayersId;
    void buildTree();

};

#endif //TOY_PROJECT_TREE_BUILDER_H
