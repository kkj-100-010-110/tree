#ifndef _RB_HPP_
#define _RB_HPP_

#include "rb.h"

template <typename K, typename D>
RB<K, D>::RB() : root(nullptr) {};

template <typename K, typename D>
RB<K, D>::Node::Node(const K& key, const D& data, Color color, int size)
    : key(key), data(data), color(color), size(size), left(nullptr), right(nullptr) {}

template <typename K, typename D>
bool RB<K, D>::_isRed(Node*& node) const
{
    if (!node) return BLACK; // null(nil) nodes are black.
    return node->color == RED;
}

template <typename K, typename D>
bool RB<K, D>::empty() const { return !root; }

template <typename K, typename D>
int RB<K, D>::size() const { return _size(root); }

template <typename K, typename D>
const D& RB<K, D>::find(const K& key)
{
    Node*& check = _find(root, key);
    if (!check) throw std::runtime_error("ERROR::_find()::key not found.");
    return check->data;
}

template <typename K, typename D>
bool RB<K, D>::contain(const K& key) { return _find(key, root) != nullptr; }

template <typename K, typename D>
const K& RB<K, D>::min() const
{
    if (empty()) throw std::runtime_error("ERROR::min()::it is empty.");
    return _min(root)->key;
}

template <typename K, typename D>
const K& RB<K, D>::max() const
{
    if (empty()) throw std::runtime_error("ERROR::max()::it is empty.");
    return _max(root)->key;
}

template <typename K, typename D>
int RB<K, D>::_size(Node*& node) const 
{ 
    if (!node) return 0;
    return node->size;
}

template <typename K, typename D>
typename RB<K, D>::Node*& RB<K, D>::_find(const K& key, Node*& node) const
{
    if (!node) return node;
    else if (key < node->key) return _find(key, node->left);
    else if (key > node->key) return _find(key, node->right);
    else return node; // key == node->key
}

template <typename K, typename D>
typename RB<K, D>::Node*& RB<K, D>::_min(Node*& node)
{
    return node->left == nullptr ? node : _min(node->left);
}

template <typename K, typename D>
typename RB<K, D>::Node*& RB<K, D>::_max(Node*& node)
{
    return node->right == nullptr? node : _max(node->right);
}


template <typename K, typename D>
void RB<K, D>::insert(const K& key, const D& data)
{
    _insert(root, key, data);
    root->color = BLACK;
}

template <typename K, typename D>
void RB<K, D>::_insert(Node*& node, const K& key, const D& data)
{
    if (!node) {
        node = new Node(key, data, RED, 1);
        return;
    }
    else if (node->key < key) {
        _insert(node->right, key, data);
        _fixUp(node);
        return;
    }
    else if (node->key > key) {
        _insert(node->left, key, data);
        _fixUp(node);
        return;
    }
    else { // node->key == key, then the node with the key update a new data.
        Node* tmp = node;
        Node* n = new Node(node->key, data, node->color, node->size);
        n->left = node->left;
        n->right = node->right;
        node = n;
        delete tmp;
        return;
    }
}

template <typename K, typename D>
void RB<K, D>::_fixUp(Node*& node)
{
    if (!node) return ;
    if (_isRed(node->right) && !_isRed(node->left))
        _rotateLeft(node);
    if (_isRed(node->left) && _isRed(node->left->left))
        _rotateRight(node);
    if (_isRed(node->left) && _isRed(node->right))
        _colorFlip(node);

    node->size = 1 + _size(node->left) + _size(node->right);
}

template <typename K, typename D>
void RB<K, D>::_rotateRight(Node*& node)
{
    Node* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    tmp->color = node->color;
    node->color = RED;
    tmp->size = node->size;
    node->size = 1 + _size(node->left) + _size(node->right);
    node = tmp;
}

template <typename K, typename D>
void RB<K, D>::_rotateLeft(Node*& node)
{
    Node* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    tmp->color = node->color;
    node->color = RED;
    tmp->size = node->size;
    node->size = 1 + _size(node->left) + _size(node->right);
    node = tmp;
}

template <typename K, typename D>
void RB<K, D>::_colorFlip(Node*& node)
{
    node->color = _colorChange(node->color);
    node->left->color = _colorChange(node->left->color);
    node->right->color = _colorChange(node->right->color);
}

template <typename K, typename D>
typename RB<K, D>::Color RB<K, D>::_colorChange(Color c) { return c == BLACK ? RED : BLACK; }

template <typename K, typename D>
void RB<K, D>::deleteMin()
{
    _deleteMin(root);
    if (!empty()) root->color = BLACK;
}

template <typename K, typename D>
void RB<K, D>::_deleteMin(Node*& node)
{
    if (!node->left) {
        delete node;
        node = nullptr;
        return;
    }

    if (!_isRed(node->left) && !_isRed(node->left->left))
        _moveRedLeft(node);
    
    _deleteMin(node->left);
    _fixUp(node);
}

template <typename K, typename D>
void RB<K, D>::_moveRedLeft(Node*& node)
{
    _colorFlip(node);
    if (_isRed(node->right->left)) {
        _rotateRight(node->right);
        _rotateLeft(node);
        _colorFlip(node);
    }
}

template <typename K, typename D>
void RB<K, D>::deleteMax()
{
    _deleteMax(root);
    if (!empty()) root->color = BLACK;
}

template <typename K, typename D>
void RB<K, D>::_deleteMax(Node*& node)
{
    if (_isRed(node->left)) _rotateRight(node);

    if (!node->right) {
        delete node;
        node = nullptr;
        return;
    }

    if (!_isRed(node->right) && !_isRed(node->right->left))
        _moveRedRight(node);

    _deleteMax(node->right);

    _fixUp(node);
}

template <typename K, typename D>
void RB<K, D>::_moveRedRight(Node*& node)
{
    _colorFlip(node);
    if (_isRed(node->left->left)) {
        _rotateRight(node);
        _colorFlip(node);
    }
}

template <typename K, typename D>
void RB<K, D>::clear()
{
    while (root)
        remove(root->key);
}

template <typename K, typename D>
void RB<K, D>::remove(const K& key)
{
    if (!contain(key)) {
        std::cout << "Error::remove():: there is not the node with the key" << std::endl;
        return;
    }
    _remove(root, key);
    if (!empty()) root->color = BLACK;
}

template <typename K, typename D>
void RB<K, D>::_remove(Node*& node, const K& key)
{
    if (key < node->key) { // when the search path is towards the left sub-tree of the node, similar to deleteMin()
        if (!_isRed(node->left) && !_isRed(node->left->left))
            _moveRedLeft(node);
        _remove(node->left, key);
    }
    else { // when the search path is towards the right sub-tree of the node, similar to deleteMax() and when it finds the target
        if (_isRed(node->left)) _rotateRight(node);

        // when found the key and its right-sub-tree doesn't exist
        if (key == node->key && node->right == nullptr) {
            delete node;
            node = nullptr;
            return;
        }

        if (!_isRed(node->right) && !_isRed(node->right->left))
            _moveRedRight(node);
        
        if (key == node->key) { // replace the target node with the minimum node on its right child.
            Node* tmp = _min(node->right);
            Node* replace = new Node(tmp->key, tmp->data, node->color, node->size);
            replace->left = node->left;
            replace->right = node->right;
            tmp = node;
            node = replace;
            delete tmp;
            tmp = nullptr;
            _deleteMin(node->right);
        }
        else
            _remove(node->right, key);
    }
    _fixUp(node);
}

template <typename K, typename D>
int RB<K, D>::height() const { return _height(root); }

template <typename K, typename D>
int RB<K, D>::_height(Node*& node)
{
    if (!node)
        return -1;
    return 1 + std::max(_height(node->left), _height(node->right));
}

/* Print */
template <typename K, typename D>
void RB<K, D>::print(int order)
{
    if (empty()) {
        std::cout << "It's empty" << std::endl;
        return;
    }
    switch (order)
    {
        case 1: _print_inorder(root); break;
        case 2: _print_preorder(root); break;
        case 3: _print_postorder(root); break;
        case 4: _print_level(); break;
        default : std::cout << "Wrong number for order" << std::endl;
    }
    std::cout << std::endl;
}

template <typename K, typename D>
void RB<K, D>::_print_preorder(Node* cur) // root->left->right
{
    if (!cur)
        return;
    std::cout << cur->data << " ";
    _print_preorder(cur->left);
    _print_preorder(cur->right);
}

template <typename K, typename D>
void RB<K, D>::_print_inorder(Node* cur) // left->root->right
{
    if (!cur)
        return;
    _print_inorder(cur->left);
    std::cout << cur->data << " ";
    _print_inorder(cur->right);
}

template <typename K, typename D>
void RB<K, D>::_print_postorder(Node* cur) // left->right->root
{
    if (!cur)
        return;
    _print_postorder(cur->left);
    _print_postorder(cur->right);
    std::cout << cur->data << " ";
}

template <typename K, typename D>
void RB<K, D>::_print_level()
{
    int depth = 0;
    std::queue<Node *> q;
    q.push(root);
    while (q.size())
    {
        std::cout << "Depth-" << depth << ": ";
        int size = q.size();
        for (int i = 0; i < size; i++)
        {
            Node *tmp = q.front();
            q.pop();
            if (tmp->color == RED)
                std::cout << "\033[0;31m" << tmp->key << "(" << tmp->size << ")" "\033[0m";
            else
                std::cout << tmp->key << "(" << tmp->size << ")";
            if (tmp->left)
            {
                std::cout << "[L-" << tmp->left->key << "]";
                q.push(tmp->left);
            }
            if (tmp->right)
            {
                std::cout << "[R-" << tmp->right->key << "]";
                q.push(tmp->right);
            }
            std::cout << "  ";
        }
        std::cout << std::endl;
        depth++;
    }
    std::cout << "--------------------------------------------------------------------------------------------------------";
}

#endif //_RB_HPP_