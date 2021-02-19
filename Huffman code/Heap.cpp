#include <iostream>
#include <string>
#include <iomanip>
#include "Heap.hpp"

using namespace std;

//swap -key-, -cou-, -left-, -right- and -code- of the given two nodes
void swap(HuffmanNode *a, HuffmanNode *b)
{
    struct HuffmanNode *t = new struct HuffmanNode;

    t->key = a->key;
    a->key = b->key;
    b->key = t->key;

    t->cou = a->cou;
    a->cou = b->cou;
    b->cou = t->cou;

    t->left = a->left;
    a->left = b->left;
    b->left = t->left;

    t->right = a->right;
    a->right = b->right;
    b->right = t->right;

    t->code = a->code;
    a->code = b->code;
    b->code = t->code;
}

//initialize -HeapSize-, -capacity- and -nodes-
Heap::Heap()
{
    HeapSize = 0;
    capacity = 256;
    nodes = new struct HuffmanNode*[capacity];
}

//<<recursion>> heapify from the given index
void Heap::heapify(const int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if(l < HeapSize && nodes[l]->cou < nodes[smallest]->cou)
        smallest = l;
    if(r < HeapSize && nodes[r]->cou < nodes[smallest]->cou)
        smallest = r;
    if(smallest != i)
    {
        swap(nodes[i], nodes[smallest]);
        heapify(smallest);
    }
}

//insert the given node into -nodes-
void Heap::insert_node(struct HuffmanNode *new_node)
{
    int i = HeapSize++;
    nodes[i] = new_node;
    while(i != 0 && nodes[i]->cou < nodes[parent(i)]->cou)
    {
        swap(nodes[i], nodes[parent(i)]);
        i = parent(i);
    }
}

//extract the min node
//return the root of the main heap
struct HuffmanNode* Heap::extract_min()
{
    struct HuffmanNode *root = new struct HuffmanNode;
    root = nodes[0];
    nodes[0] = nodes[--HeapSize];
    heapify(0);
    return root;
}

