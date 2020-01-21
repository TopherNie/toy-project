//
// Created by Administrator on 2020/1/15 0015.
//

#ifndef TOY_PROJECT_TREE_BUILDER_H
#define TOY_PROJECT_TREE_BUILDER_H

#include <tree.hpp>
#include <state.h>
#include <constants.h>

class TreeBuilder
{
private:
    static PlayerNodeInfo* getNextPlayerInfo(int currentPlayerId, const vector<PlayerNodeInfo*>& playerNodeInfoVec);
    vector<Node<NodeVal*>*> getPlayChildren(NodeVal* parentVal);

public:
    // The first ID in this vector is the first player of this round
    void buildTreeR(Node<NodeVal*>* root);

};

#endif //TOY_PROJECT_TREE_BUILDER_H
