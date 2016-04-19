#ifndef _RB_TREE_H_
#define _RB_TREE_H_

const bool BLACK = false;
const bool RED = true;

template<typename Key, typename Value> class rb_tree
{
    public:
        struct Node
        {
            Node(Key key, Value)
            {
                this->key   = key;
                this->value = value;
                this->color = RED;
            }

            Node()
            {
                this->left  = nullptr;
                this->right = nullptr;
                this->parent= nullptr;
                this->color = BLACK;
            }

            //private:
            //enum { BLACK = false, RED = true };

            //private:
                Key     key;
                Value   value;
                bool    color;
                Node*   left;
                Node*   right;
                Node*   parent;
        };

    public:
        rb_tree() : nil(new Node), root(nil) {}
        ~rb_tree() {}

        void insert(Key key, Value value);
        void remove(Key key);
        Node* search(Key key);

        void dump();
    private:
        void rotate_left(Node* node);
        void rotate_right(Node* node);

        void del_node(Node* node);
        void del_fixup(Node* node);
        void transplant(Node* u, Node* v);

        void insert_fixup(Node* node);

        Node* successor(Node* node);

        void dump(Node* node);

        Node*   nil;        // nil node
        Node*   root;       // root node
};

template<typename Key, typename Value>
void rb_tree<Key, Value>::insert(Key key, Value value)
{
    rb_tree<Key, Value>::Node* node = new rb_tree<Key, Value>::Node(key, value);
    rb_tree<Key, Value>::Node* curr = root;
    rb_tree<Key, Value>::Node* next = root;
    while (next != nil) 
    {
        curr = next;
        if (key < curr->key)
            next = curr->left;
        else
            next = curr->right;
    }
    node->parent = curr;
    if (curr == nil)
    {
        root = node;
    }
    else {
        if (node->key < curr->key)
            curr->left = node;
        else
            curr->right = node;
    }
    node->left = nil;
    node->right = nil;
    node->color = RED;

    // fixup
    insert_fixup(node);
}

template<typename Key, typename Value>
typename rb_tree<Key, Value>::Node* rb_tree<Key, Value>::search(Key key)
{
    rb_tree<Key, Value>::Node* curr = root;
    while(curr != nil && key != curr->key)
    {
        if (key < curr->key)
            curr = curr->left;
        else
            curr = curr->right;
    }

    return curr;
}

template<typename Key, typename Value>
void rb_tree<Key, Value>::remove(Key key)
{
    rb_tree<Key, Value>::Node* node = search(key);
    if (node != nil)
    {
        del_node(node);
    }
}

template<typename Key, typename Value>
typename rb_tree<Key, Value>::Node* rb_tree<Key, Value>::successor(rb_tree<Key, Value>::Node* node)
{
    if (node->right != nil)
    {
        while (node->left != nil)
            node = node->left;
        return node;
    }

    rb_tree<Key, Value>::Node* curr = node->parent;
    while (curr != nil && node == curr->right)
    {
        node = curr;
        curr = curr->parent;
    }

    return curr;
}

template<typename Key, typename Value>
void rb_tree<Key, Value>::rotate_left(rb_tree<Key, Value>::Node* node)
{
    rb_tree<Key, Value>::Node* s = node->right;
    if (s->parent == nil)
    {
        root = s;
    }
    else
    {
        if (node == node->parent->left)
            node->parent->left = s;
        else
            node->parent->right = s;
    }

    s->parent = node->parent;
    node->right = s->left;
    s->left->parent = node;
    s->left = node;
    node->parent = s;
}

template<typename Key, typename Value>
void rb_tree<Key, Value>::rotate_right(rb_tree<Key, Value>::Node* node)
{
    rb_tree<Key, Value>::Node* s = node->left;
    if (node->parent == nil)
    {
        root = s;
    }
    else
    {
        if (node == node->parent->left)
            node->parent->left = s;
        else
            node->parent->right = s;
    }

    s->parent = node->parent;
    node->left = s->right;
    s->right->parent = node;
    s->right = node;
    node->parent = s;
}

template<typename Key, typename Value>
void rb_tree<Key, Value>::insert_fixup(rb_tree<Key, Value>::Node* node)
{
    while (node->parent->color == RED)
    {
        if (node->parent == node->parent->parent->left)
        {
            rb_tree<Key, Value>::Node* p_r = node->parent->parent->right;
            if (p_r->color == RED)
            {
                node->parent->color = BLACK;
                p_r->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    rotate_left(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotate_right(node->parent->parent);
            }
        }
        else
        {
            rb_tree<Key, Value>::Node* p_l = node->parent->parent->left;
            if (p_l->color == RED)
            {
                node->parent->color = BLACK;
                p_l->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    rotate_right(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotate_left(node->parent->parent);
            }
        }
    }

    root->color = BLACK;
}

template<typename Key, typename Value>
void rb_tree<Key, Value>::transplant(rb_tree<Key, Value>::Node* u, rb_tree<Key, Value>::Node* v)
{
    if (u->parent == nil)
    {
        root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent.left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

template<typename Key, typename Value>
void rb_tree<Key, Value>::del_node(rb_tree<Key, Value>::Node* node)
{
    rb_tree<Key, Value>::Node* x = nil;
    rb_tree<Key, Value>::Node* y = nil;

    if (node->left == nil || node->right == nil)
        y = node;
    else
        y = successor(node);

    if (y->left != nil)
        x = y->left;
    else
        x = y->right;
    x->parent = y->parent;
    if (y->parent == nil)
        root = x;
    else
    {
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }
    if (y != node)
    {
        node->key = y->key;
        node->value = y->value;
    }

    if (y->color == BLACK)
    {
        del_fixup(x);
    }

    delete y;

}

template<typename Key, typename Value>
void rb_tree<Key, Value>::del_fixup(rb_tree<Key, Value>::Node* node)
{
    while (node != root && node->color == BLACK)
    {
        rb_tree<Key, Value>::Node* u = nullptr;
        if (node == node->parent->left)
        {
            u = node->parent->right;
            if (u->color == RED)
            {
                u->color = BLACK;
                node->parent->color = RED;
                rotate_left(node->parent);
                u = node->parent->right;
            }
            if (u->left->color == BLACK && u->right->color == BLACK)
            {
                u->color = RED;
                node = node->parent;
            }
            else
            {
                if (u->right->color == BLACK)
                {
                    u->left->color = BLACK;
                    u->color = RED;
                    rotate_right(u);
                    u = u->parent->right;
                }
                u->color = node->parent->color;
                node->parent->color = BLACK;
                u->right->color = BLACK;
                rotate_left(node->p);
                node = root;
            }
        }
        else
        {
            u = node->parent->left;
            if (u->color == RED)
            {
                u->color = BLACK;
                node->parent->color = RED;
                rotate_right(node->parent);
                u = u->parent->left;
            }

            if (u->right->color == BLACK && u->left->color == BLACK)
            {
                u->color = RED;
                node = node->parent;
            }
            else
            {
                if (u->left->color == RED)
                {
                    u->right->color = BLACK;
                    u->color = RED;
                    rotate_left(u);
                    u = node->parent->left;
                }

                u->color = node->parent->color;
                node->parent->color = BLACK;
                u->left->color = BLACK;
                rotate_right(node->parent);
                node = root;
            }
        }
    }

    node->color = BLACK;
}


template<typename Key, typename Value>
void rb_tree<Key, Value>::dump()
{
    if (root == nil)
    {
        std::cout << "Tree is empty!" << std::endl;
    }
    else
    {
        dump(root);
    }
}

template<typename Key, typename Value>
void rb_tree<Key, Value>::dump(rb_tree<Key, Value>::Node* node)
{
    if (node->left != nil)
    {
        dump(node->left);
    }
    if (node != nil)
    {
        std::cout << node->key << " ";
        if (node->color == RED)
        {
            std::cout << "RED ";
        }
        else
        {
            std::cout << "BLACK ";
        }
        if (node->parent != nil)
        {
            std::cout << node->parent->key << " ";
        }
        else
        {
            std::cout << "NIL ";
        }
        if (node->left != nil)
        {
            std::cout << node->left->key << " ";
        }
        else
        {
            std::cout << "NIL ";
        }
        if (node->right != nil)
        {
            std::cout << node->right->key << " ";
        }
        else
        {
            std::cout << "NIL ";
        }
    }
    std::cout << std::endl;
    if (node->right != nil)
    {
        dump(node->right);
    }
}

#endif
