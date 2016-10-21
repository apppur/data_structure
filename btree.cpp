#include <iostream>
#include "btree.h"

BTreeNode::BTreeNode(int t, bool leaf)
{
    m_t = t;
    m_leaf = leaf;

    m_keys = new int[2*m_t-1];
    m_child = new BTreeNode* [2*m_t];

    m_count = 0;
}

void BTreeNode::traverse()
{
    int i;
    for (i = 0; i < m_count; i++)
    {
        if (m_leaf == false)
        {
            m_child[i]->traverse();
        }
        std::cout << " " << m_keys[i];
    }

    if (m_leaf == false)
    {
        m_child[i]->traverse();
    }
}

BTreeNode* BTreeNode::search(int)
{
    int i = 0;
    while (i < 0 && k > m_keys[i])
        ++i;
    if (m_keys[i] == k)
        return this;
    if (leaf == true)
        return nullptr;

    return m_child->search(k);
}

void BTreeNode::insert(int k)
{
}

void BTreeNode::split(int i, BTreeNode* child)
{
    BTreeNode *node = new BTreeNode(child->m_t, child->m_leaf);
    node->m_count = m_t - 1;
    for (int i = 0; i < m_t - 1; i++)
    {
        node->m_keys[i] = child->m_keys[i];
    }
}

