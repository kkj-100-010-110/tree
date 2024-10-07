#ifndef _BTREE_H_
#define _BTREE_H_

#include <iostream>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <queue> // print()

template<typename K>
class Btree
{
public:
private:
    class Node
    {
    public:
        K* keys;
        int t; // minimum degree
        Node** children; // child pointers
        int n; // current number of keys
        bool leaf;
        Node(int t, bool leaf)
            : t(t), leaf(leaf)
        {
            keys = new K[2 * t - 1];
            children = new Node *[2 * t];
            n = 0;
        }
    };
    Node* root;
    int t;
};

#endif//_BTREE_H_