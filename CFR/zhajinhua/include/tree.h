//
// Created by Administrator on 2019/12/30 0030.
//

#ifndef TOY_PROJECT_TREE_H
#define TOY_PROJECT_TREE_H

#include <vector>
#include <string>
#include <array>

using namespace std;

template <typename T>
struct Node
{
    T _val;
    vector<Node<T>*> _children;

    Node(const T val, const vector<Node<T>*>& children): _val(val), _children(children){};

    void print();
};


template <class T>
class Tree{

public:
    Node<T>* _root;

    explicit Tree(Node<T>* root): _root(root){};

    Node<T>* find(T val);
    bool addNode(T parentVal, T childVal);

private:
    Node<T>* find_r(Node<T>* root, T val);


};



#endif //TOY_PROJECT_TREE_H
