#ifndef _AVL_H_
#define _AVL_H_

#include <iostream>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <queue> // print()

template<typename K, typename D> // key & data
class AVL
{
public:
    AVL() : head_(nullptr) {}

    const D& find(const K& key);
    bool contains(const K& key);
    void insert(const K& key, const D& data);
    const D& remove(const K& key);
    bool empty() const;
    void clear();
    void print(int order = 1);

private:
    class Node
    {
    public:
        const K &key;
        const D &data;
        Node *left;
        Node *right;
        int height;
        Node(const K& key, const D& data) : key(key), data(data), left(nullptr), right(nullptr), height(0) {}
    };

    Node* head_;

    Node*& _find(const K& key, Node*& cur) const;
    void _find_and_insert(const K& key, const D& data, Node*& cur);
    const D& _find_and_remove(const K& key, Node*& cur);
    const D& _remove(Node*& node);

    // targetNode is the Node to remove, so find iop(in-order predecessor) and swap the target with it for removal
    const D& _iopRemove(Node*& targetNode);
    const D& _iopRemove(Node*& targetNode, Node*& iopAncester, bool isInitialCall);
    Node*& _swap_nodes(Node*& node1, Node*& node2);

    void _updateHeight(Node*& cur);
    void _ensureBalance(Node*& cur);

    void _rotateLeft(Node*& cur);
    void _rotateRight(Node*& cur);
    void _rotateLeftRight(Node*& cur);
    void _rotateRightLeft(Node*& cur);

    int _get_height(Node*& node) const;
    int _get_balance_factor(Node*& node) const;

    void _print_inorder(Node *cur);
    void _print_preorder(Node *cur);
    void _print_postorder(Node *cur);
    void _print_level();
};

#endif//_AVL_H_