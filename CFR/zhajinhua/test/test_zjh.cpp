//
// Created by Administrator on 2020/1/14 0014.
//

#include <card.h>
#include <tools.h>
#include <tree_builder.h>

void testCardAnalyze()
{
    vector<string> cards_1{"7c", "6d", "4h", "4s"};
    int type{};
    vector<int> winRanks_1{};
    vector<int> winCardIndexes_1{};
    analyzeCards(cards_1, type, winRanks_1, winCardIndexes_1);
    cout << vecToString(winRanks_1) << endl;
}

void testTreeBuild()
{
    auto* treeBuilder = new TreeBuilder;
    auto* playInfo0 = new PlayerNodeInfo;
    playInfo0->roundBet = BASIC_BET;
    auto* playInfo1 = new PlayerNodeInfo;
    playInfo1->roundBet = 2 * BASIC_BET;
    auto* rootVal = new NodeVal;
    rootVal->playerNodeInfoVec.push_back(playInfo0);
    rootVal->playerNodeInfoVec.push_back(playInfo1);
    rootVal->currentPlayerId = playInfo0->playerID;
    auto* root = new Node<NodeVal*>(rootVal);
    treeBuilder->buildTreeR(root);
    root->print();
}

int main()
{
    testTreeBuild();
}
