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
    // The first ID in this vector is the first player of this round
    vector<int> inPlayerIDs;
    void buildTree();

};

#endif //TOY_PROJECT_TREE_BUILDER_H
