#ifndef _BTREE_H
#define _BTREE_H

class BTreeNode
{
    int *m_keys;
    int m_t;
    BTreeNode **m_child;
    bool m_leaf;
    int m_count;

    private:
        BTreeNode(int t, bool leaf);

        void traverse();

        BTreeNode* search(int k);

        void insert(int k);
        void split(int i, BTreeNode* child);

        friend class BTree;
};

class BTree
{
    public:
        BTree(int t) : m_root(nullptr), m_t(t) {}

        void traverse()
        {
            if (m_root != nullptr) m_root->traverse();
        }

        BTreeNode* search(int k) 
        {
            return (root == nullptr) ? nullptr : m_root->search(k);
        }

        void insert(int k);
    private:
        BTreeNode *m_root;
        int m_t;
};

#endif
