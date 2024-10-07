#ifndef _RB_H_
#define _RB_H_

#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <assert.h>

template<typename K, typename D>
class RB
{
public:
    RB();
    bool empty() const;
    int size() const;
    const D& find(const K& key);
    bool contain(const K& key);
    const K& min() const;
    const K& max() const;
    int height() const;
    void insert(const K& key, const D& data);
    void remove(const K &key);
    void clear();
    void print(int order);

    // warm-up for delete()
    void deleteMin();
    void deleteMax();

private:
    enum Color { BLACK = 0, RED = 1 };

    class Node
    {
    public:
        const K& key;
        const D& data;
        Color color;
        int size; // the number of its sub-tree 
        Node* left;
        Node* right;
        Node(const K& key, const D& data, Color color, int size);
    };

    Node* root;

    bool _isRed(Node*& node) const;
    int _size(Node*& node) const;
    Node*& _find(const K& key, Node*& node) const;
    Node*& _min(Node*& node);
    Node*& _max(Node*& node);

    void _insert(Node*& node, const K& key, const D& data);
    void _remove(Node*& node, const K& key);

    void _fixUp(Node*& node);
    void _rotateRight(Node*& node);
    void _rotateLeft(Node*& node);
    void _colorFlip(Node*& node);
    Color _colorChange(Color c);

    void _deleteMin(Node*& node);
    void _deleteMax(Node*& node);
    void _moveRedLeft(Node*& node);
    void _moveRedRight(Node*& node);

    int _height(Node*& node);
    void _print_preorder(Node* cur);
    void _print_inorder(Node* cur);
    void _print_postorder(Node* cur);
    void _print_level();
};

#endif //_RB_H_