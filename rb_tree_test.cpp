#include <iostream>
#include <ctime>
#include "rb_tree.h"

using namespace std;

const int MAX = 15;

int main(int argc, char** argv)
{
    rb_tree<int, int> rbtree;
    srand((unsigned)time(nullptr));
    srand(rand());
    srand(rand());

    for (int i = 0; i != MAX; i++)
    {
        rbtree.insert(rand(), rand());
    }
    rbtree.dump();

    return 0;
}
