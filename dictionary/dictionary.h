#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <iostream>
#include <stdexcept>
#include <queue>

template<typename K, typename D>
class Dictionary
{
public:
    Dictionary();
    ~Dictionary();
    void clear_tree();
    bool empty() const;
    const D& find(const K& key);
    void insert(const K& key, const D& data);
    const D& remove(const K& key);
    const D& max() const;
    const D& min() const;
    void print();

private:
    class TreeNode
    {
    public:
        const K& key;
        const D& data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const K& key, const D& data);
    };

    TreeNode* root_;

    // all in private to hide the information
    const D& _max(TreeNode* cur) const;
    const D& _min(TreeNode* cur) const;

    TreeNode*& _find(const K& key, TreeNode*& cur) const;
    const D& _remove(TreeNode*& node);
    TreeNode*& _predecessor(TreeNode*& cur) const;
    TreeNode*& _successor(TreeNode*& cur) const;
    TreeNode*& _rightmost(TreeNode*& cur) const;
    TreeNode*& _leftmost(TreeNode*& cur) const;
    TreeNode*& _swap(TreeNode*& node1, TreeNode*& node2);
};

#endif//_DICTIONARY_H_