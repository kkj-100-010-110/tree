#ifndef _AVL_HPP_
#define _AVL_HPP_

#include "avl.h"

template <typename K, typename D>
const D& AVL<K, D>::find(const K& key)
{
    Node *&node = _find(key, head_);
    if (!node)
        throw std::runtime_error("ERROR::FIND::key not found");
    return node->data;
}

template <typename K, typename D>
bool AVL<K, D>::contains(const K& key)
{
    return _find(key, head_) != nullptr;
}

template<typename K, typename D>
void AVL<K, D>::insert(const K& key, const D& data)
{
    _find_and_insert(key, data, head_);
}

template <typename K, typename D>
bool AVL<K, D>::empty() const { return !head_; }

template <typename K, typename D>
void AVL<K, D>::clear()
{
    while (head_)
        remove(head_->key);
}

template<typename K, typename D>
const D& AVL<K, D>::remove(const K& key) { return _find_and_remove(key, head_); }

template<typename K, typename D>
typename AVL<K, D>::Node*& AVL<K, D>::_find(const K& key, Node*& cur) const
{
    if (!cur)
        return cur;
    else if (key == cur->key)
        return cur;
    else if (key < cur->key)
        return _find(key, cur->left);
    else
        return _find(key, cur->right);
}

template <typename K, typename D>
void AVL<K, D>::_find_and_insert(const K& key, const D& data, Node*& cur)
{
    if (!cur) {
        cur = new Node(key, data);
        return;
    }
    else if (cur->key == key) {
        throw std::runtime_error("ERROR::INSERT::key already exists");
    }
    else if (cur->key > key) {
        _find_and_insert(key, data, cur->left);
        _ensureBalance(cur);
        return ;
    }
    else {
        _find_and_insert(key, data, cur->right);
        _ensureBalance(cur);
        return ;
    }
}

template <typename K, typename D>
const D &AVL<K, D>::_find_and_remove(const K& key, Node*& cur)
{
    if (!cur) throw std::runtime_error("ERROR::FIND_AND_REMOVE::key not found");
    else if (cur->key == key) return _remove(cur);
    else if (cur->key < key)
    {
        const D& data = _find_and_remove(key, cur->right);
        _ensureBalance(cur);
        return data;
    }
    else
    {
        const D& data = _find_and_remove(key, cur->left);
        _ensureBalance(cur);
        return data;
    }
}

template <typename K, typename D>
const D& AVL<K, D>::_remove(Node*& node)
{
    if (!node) throw std::runtime_error("ERROR::REMOVE::the function used on nullptr");
    
    if (!node->left && !node->right) // when the node has no children.
    {
        const D& data = node->data;
        delete node;
        node = nullptr;
        return data;
    }
    else if (node->left && !node->right) // when the node has its left child only.
    {
        const D& data = node->data;
        Node* temp = node;
        node = node->left;
        delete temp;
        temp = nullptr;
        return data;
    }
    else if (!node->left && node->right) // when the node has its right child only.
    {
        const D& data = node->data;
        Node* temp = node;
        node = node->right;
        delete temp;
        temp = nullptr;
        return data;
    }
    else // when the node has two children.
    {
        return _iopRemove(node);
    }
}


template <typename K, typename D>
const D& AVL<K, D>::_iopRemove(Node*& targetNode)
{
    if (!targetNode) throw std::runtime_error("ERROR::IOP_REMOVE:: this function called on nullptr");

    const D& data = _iopRemove(targetNode, targetNode->left, true);

    if (targetNode->left)
        _ensureBalance(targetNode->left);
    _ensureBalance(targetNode);
    return data;
}

template <typename K, typename D>
const D& AVL<K, D>::_iopRemove(Node*& targetNode, Node*& iopAncester, bool isInitialCall)
{
    if (!targetNode) throw std::runtime_error("ERROR::IOP_REMOVE:: targetNode is nullptr");
    if (!iopAncester) throw std::runtime_error("ERROR::IOP_REMOVE:: iopAncester is nullptr");

    if (!iopAncester->right)
    {
        const D &data = _iopRemove(targetNode, iopAncester->right, false);
        if (!isInitialCall)
            if (iopAncester)
                _ensureBalance(iopAncester);
        return data;
    }
    else
    {
        Node*& movedTarget = _swap_nodes(targetNode, iopAncester);
        const D& data = _remove(movedTarget);
        return data;
    }
}

template <typename K, typename D>
typename AVL<K, D>::Node*& AVL<K, D>::_swap_nodes(Node*& node1, Node*& node2)
{
    Node* orig_node1 = node1;
    Node* orig_node2 = node2;
    std::swap(node1->height, node2->height);
    if (node1->left == node2)
    {
        std::swap(node1->right, node2->right);
        node1->left = orig_node2->left;
        orig_node2->left = node1;
        node1 = orig_node2;
        return node1->left;
    }
    else if (node1->right == node2)
    {
        std::swap(node1->left, node2->left);
        node1->right = orig_node2->right;
        orig_node2->right = node1;
        node1 = orig_node2;
        return node1->right;
    }
    else if (node2->left == node1)
    {
        std::swap(node2->right, node1->right);
        node2->left = orig_node1->left;
        orig_node1->left = node2;
        node2 = orig_node1;
        return node2->left;
    }
    else if (node2->right == node1)
    {
        std::swap(node2->left, node1->left);
        node2->right = orig_node1->right;
        orig_node1->right = node2;
        node2 = orig_node1;
        return node2->right;
    }
    else
    {
        std::swap(node1->left, node2->left);
        std::swap(node1->right, node2->right);
        std::swap(node1, node2);
        return node2;
    }
}

template <typename K, typename D>
void AVL<K, D>::_updateHeight(Node*& cur)
{
    if (!cur) return;
    cur->height = 1 + std::max(_get_height(cur->left), _get_height(cur->right));
}

template <typename K, typename D>
void AVL<K, D>::_ensureBalance(Node*& cur)
{
    if (!cur) return;

    // Calculate balance factor for this node
    int initial_balance = _get_balance_factor(cur);
    // Error checking
    if (initial_balance < -2 || initial_balance > 2)
    {
        std::string msg("ERROR::INITIAL_BALANCE_FACTOR::");
        msg += std::to_string(initial_balance);
        std::cerr << "Key: " << cur->key << "- Data: " << cur->data << std::endl;
        std::cerr << "L-Key: " << cur->left->key << "- R-Key: " << cur->right->key << std::endl;
        std::cerr << "L-H: " << _get_height(cur->left) << "- R-H: " << _get_height(cur->right) << std::endl;
        throw std::runtime_error(msg);
    }

    // Check the balance in direction of imbalance.
    if (initial_balance == -2)
    {
        const int left_balance = _get_balance_factor(cur->left);
        if ((left_balance == -1) || (left_balance == 0))
            _rotateRight(cur);
        else if (left_balance == 1)
            _rotateLeftRight(cur);
        else // Error checking
        {
            std::string msg("ERROR::left_balance has an unexpected value: ");
            msg += std::to_string(left_balance);
            throw std::runtime_error(msg);
        }
    }
    else if (initial_balance == 2)
    {
        const int right_balance = _get_balance_factor(cur->right);
        if ((right_balance == 1) || (right_balance == 0))
            _rotateLeft(cur);
        else if (right_balance == -1)
            _rotateRightLeft(cur);
        else // Error checking
        {
            std::string msg("ERROR::right_balance has an unexpected value: ");
            msg += std::to_string(right_balance);
            throw std::runtime_error(msg);
        }
    }

    _updateHeight(cur);

    const int final_balance = _get_balance_factor(cur);
    if (final_balance < -1 || final_balance > 1)
    {
        std::string msg("ERROR::FINAL_BALANCE::invalid balance factor: ");
        msg += std::to_string(final_balance);
        throw std::runtime_error(msg);
    }
}

template <typename K, typename D>
void AVL<K, D>::_rotateLeft(Node*& cur)
{
    if (!cur) throw std::runtime_error("ERROR::ROTATION::LEFT::node is nullptr");
    if (!cur->right) throw std::runtime_error("ERROR::ROTATION::LEFT::node's right is nullptr");

    Node* x = cur;
    Node* y = cur->right;
    Node* z = cur->right->left;

    x->right = z;
    y->left = x;
    cur = y;

    _updateHeight(x);
    _updateHeight(y);
}

template <typename K, typename D>
void AVL<K, D>::_rotateRight(Node*& cur)
{
    if (!cur) throw std::runtime_error("ERROR::ROTATION::RIGHT::node is nullptr");
    if (!cur->left) throw std::runtime_error("ERROR::ROTATION::RIGHT::node's left is nullptr");

    Node* x = cur;
    Node* y = cur->left;
    Node* z = cur->left->right;

    x->left = z;
    y->right = x;
    cur = y;

    _updateHeight(x);
    _updateHeight(y);
}

template <typename K, typename D>
void AVL<K, D>::_rotateLeftRight(Node*& cur)
{
    if (!cur) throw std::runtime_error("ERROR::ROTATION::LEFT_RIGHT::node is nullptr");

    _rotateLeft(cur->left);
    _rotateRight(cur);
}

template <typename K, typename D>
void AVL<K, D>::_rotateRightLeft(Node*& cur)
{
    if (!cur) throw std::runtime_error("ERROR::ROTATION::RIGHT_LEFT::node is nullptr");

    _rotateRight(cur->right);
    _rotateLeft(cur);
}

template <typename K, typename D>
int AVL<K, D>::_get_height(Node*& node) const
{
    if (!node) return -1; // non-existent node has a height of -1
    else return node->height;
}

template <typename K, typename D>
int AVL<K, D>::_get_balance_factor(Node*& node) const
{
    if (!node) return 0; // non-existent node has a balance factor of 0
    else return _get_height(node->right) - _get_height(node->left);
}

template <typename K, typename D>
void AVL<K, D>::print(int order)
{
    switch (order)
    {
        case 1: _print_inorder(head_); break;
        case 2: _print_preorder(head_); break;
        case 3: _print_postorder(head_); break;
        case 4: _print_level(); break;
        default : std::cout << "Wrong number for order" << std::endl;
    }
    std::cout << std::endl;
}

template <typename K, typename D>
void AVL<K, D>::_print_preorder(Node* cur) // root->left->right
{
    if (!cur)
        return;
    std::cout << cur->data << " ";
    _print_preorder(cur->left);
    _print_preorder(cur->right);
}

template <typename K, typename D>
void AVL<K, D>::_print_inorder(Node* cur) // left->root->right
{
    if (!cur)
        return;
    _print_inorder(cur->left);
    std::cout << cur->data << " ";
    _print_inorder(cur->right);
}

template <typename K, typename D>
void AVL<K, D>::_print_postorder(Node* cur) // left->right->root
{
    if (!cur)
        return;
    _print_postorder(cur->left);
    _print_postorder(cur->right);
    std::cout << cur->data << " ";
}

template <typename K, typename D>
void AVL<K, D>::_print_level()
{
    int depth = 0;
    std::queue<Node *> q;
    q.push(head_);
    while (q.size())
    {
        std::cout << "Depth-" << depth << ": ";
        int size = q.size();
        for (int i = 0; i < size; i++)
        {
            Node *tmp = q.front();
            q.pop();
            std::cout << tmp->key << "(" << tmp->height << ")";
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

#endif//_AVL_HPP_