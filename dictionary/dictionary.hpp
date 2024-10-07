// #pragma once
#ifndef _DICTIONARY_HPP_
#define _DICTIONARY_HPP_

#include "dictionary.h"

/** constructor of Dictionary class */
template <typename K, typename D>
Dictionary<K, D>::Dictionary()
    : root_(nullptr)
{}

/** constructor of TreeNode class in  Dictionary class */
template <typename K, typename D>
Dictionary<K, D>::TreeNode::TreeNode(const K& key, const D& data)
    : key(key), data(data), left(nullptr), right(nullptr)
{}

template <typename K, typename D>
Dictionary<K, D>::~Dictionary() { clear_tree(); }

template <typename K, typename D>
void Dictionary<K, D>::clear_tree()
{
    while (root_)
        remove(root_->key);
}

template <typename K, typename D>
bool Dictionary<K, D>::empty() const { return !root_; }

/** the right-most data of the tree */
template <typename K, typename D>
const D& Dictionary<K, D>::max() const { return _max(root_); }

/** the left-most data of the tree */
template <typename K, typename D>
const D& Dictionary<K, D>::min() const { return _min(root_); }

template <typename K, typename D>
const D& Dictionary<K, D>::_max(TreeNode* cur) const
{
    while (cur && cur->right)
        cur = cur->right;
    return cur->data;
}

template <typename K, typename D>
const D& Dictionary<K, D>::_min(TreeNode* cur) const
{
    while (cur && cur->left)
        cur = cur->left;
    return cur->data;
}

/** find a data matching key value */
template <typename K, typename D>
const D& Dictionary<K, D>::find(const K& key)
{
    TreeNode*& node = _find(key, root_);
    if (node == nullptr) throw std::runtime_error("Error: key not found in _find()");
    return node->data;
}

template<typename K, typename D>
typename Dictionary<K, D>::TreeNode*& Dictionary<K, D>::_find(const K& key, TreeNode*& cur) const
{
    if (cur == nullptr || key == cur->key)
        return cur;
    else if (key < cur->key)
        return _find(key, cur->left);
    else
        return _find(key, cur->right);
}

/** insert a data with key */
template <typename K, typename D>
void Dictionary<K, D>::insert(const K& key, const D& data)
{
    TreeNode*& node = _find(key, root_);
    node = new TreeNode(key, data);
}

/** remove a node for the key value */
template <typename K, typename D>
const D& Dictionary<K, D>::remove(const K& key)
{
    TreeNode*& node = _find(key, root_);
    return _remove(node);
}

template<typename K, typename D>
const D& Dictionary<K, D>::_remove(TreeNode*& node)
{
    std::cout << std::endl;
    if (!node) {
        throw std::runtime_error("Error: _remove() used on non-existent key");
    }
    if (node->left == nullptr ) {
        const D& data = node->data;
        TreeNode* tmp = node;
        node = node->right;
        delete tmp;
        return data;
    }
    if (node->right == nullptr) {
        const D& data = node->data;
        TreeNode* tmp = node;
        node = node->left;
        delete tmp;
        return data;
    }
    TreeNode*& predecessor = _predecessor(node);
    // TreeNode*& successor = _successor(node);
    if (!predecessor)
        throw std::runtime_error("Error: predecessor not found");
    TreeNode *&moved_node = _swap(node, predecessor);
    return _remove(moved_node);
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode*& Dictionary<K, D>::_predecessor(TreeNode*& cur) const
{
    if (!cur)
        return cur;
    if (!(cur->left))
        return cur->left;
    return _rightmost(cur->left);
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode*& Dictionary<K, D>::_successor(TreeNode*& cur) const
{
    if (!cur)
        return cur;
    if (!(cur->right))
        return cur->right;
    return _leftmost(cur->right);
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode*& Dictionary<K, D>::_rightmost(TreeNode*& cur) const
{
    if (!cur || !(cur->right))
        return cur;
    return _rightmost(cur->right);
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode*& Dictionary<K, D>::_leftmost(TreeNode*& cur) const
{
    if (!cur || !(cur->left))
        return cur;
    return _leftmost(cur->left);
}

template <typename K, typename D>
typename Dictionary<K, D>::TreeNode*& Dictionary<K, D>::_swap(TreeNode*& node1, TreeNode*& node2)
{
    // for _predecessor()
    if (node1->left == node2) {
        TreeNode *tmp = node2;
        std::swap(node1->right, node2->right);
        node1->left = tmp->left;
        tmp->left = node1;
        node1 = tmp;
        return node1->left;
    }
    // for _successor()
    if (node1->right == node2)
    {
        TreeNode *tmp = node2;
        std::swap(node1->left, node2->left);
        node1->right = tmp->right;
        tmp->right = node1;
        node1 = tmp;
        return node1->right;
    }
    std::swap(node1->left, node2->left);
    std::swap(node1->right, node2->right);
    std::swap(node1, node2);
    return node2;
}

/* print nodes in each level */
template <typename K, typename D>
void Dictionary<K, D>::print()
{
    std::queue<TreeNode*> q;
    q.push(root_);
    while (!q.empty())
    {
        int size = q.size();
        for (int i = 0; i < size; i++)
        {
            std::cout << " | ";
            auto current = q.front();
            q.pop();
            std::cout << current->data << " | ";
            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
        }
        std::cout << std::endl;
    }
}

#endif//_DICTIONARY_HPP_
