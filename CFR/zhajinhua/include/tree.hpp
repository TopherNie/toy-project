//
// Created by Administrator on 2019/12/30 0030.
//

#ifndef TOY_PROJECT_TREE_HPP
#define TOY_PROJECT_TREE_HPP

#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <constants.h>
#include <tools.h>

using namespace std;

template <typename T>
struct Node
{
    T _val;
    vector<Node<T>*> _children;

    explicit Node(const T val): _val(val){};
    Node(const T val, const vector<Node<T>*>& children): _val(val), _children(children){};

    void print(int indentNum=0);
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


template <typename T>
void Node<T>::print(int indentNum)
{
    cout << repeatStr(INDENT_SYMBOL, indentNum) << "{" << endl;
    cout << repeatStr(INDENT_SYMBOL, indentNum + 1) << "val:" << _val << endl;

    if (!_children.empty())
    {
        int childIndentNum = indentNum + 1;
        cout << repeatStr(INDENT_SYMBOL, indentNum + 1) << "children:[" << endl;
        for (Node<T> *child: _children)
        {

            child->print(childIndentNum);
        }
        cout << repeatStr(INDENT_SYMBOL, indentNum + 1) << "]" << endl;
    }
    cout << repeatStr(INDENT_SYMBOL, indentNum) << "}" << endl;
}

template <typename T>
Node<T>* Tree<T>::find_r(Node<T> *root, T val)
{

    if (root->val == val)
    {
        return root;
    }
    for (auto *child: root->children)
    {
        Node<T>* res = find_r(child, val);
        if (res != nullptr)
        {
            return res;
        }
    }
    return nullptr;
}

template <typename T>
Node<T>* Tree<T>::find(T val)
{
    return find_r(_root, val);
}

template <typename T>
bool Tree<T>::addNode(T parentVal, T childVal)
{
    if (_root == nullptr)
    {
        _root = new Node<T>(childVal);
        return true;
    }
    Node<T>* parent = find(parentVal);
    if (parent != nullptr)
    {
        auto child = new Node<T>(childVal);
        parent->_children.push_back(child);
        return true;
    }
    return false;
}




#endif //TOY_PROJECT_TREE_HPP
