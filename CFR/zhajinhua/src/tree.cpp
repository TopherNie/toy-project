//
// Created by Administrator on 2020/1/14 0014.
//

#include <tree.h>
#include <iostream>

using namespace std;

template <typename T>
void Node<T>::print() 
{
    cout << "{" << endl;
    cout << "\tval:" << _val << endl;
    
    if (!_children.empty())
    {
        cout << "\tchildren:[" << endl;
        for (Node<T> *child: _children)
        {
            child->print();
        }
        cout << "]" << endl;
    }
    cout << "}" << endl;
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
