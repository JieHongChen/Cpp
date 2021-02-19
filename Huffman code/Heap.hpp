#ifndef HEAP_HPP
#define HEAP_HPP
#include <iostream>
#include <map>

using namespace std;

struct HuffmanNode
{
    char key;
    int cou = 0;
    struct HuffmanNode *left = NULL;
    struct HuffmanNode *right = NULL;
    string code;
};

class Heap
{
    public:
        Heap();
        int parent(const int i) const {return (i - 1) / 2;}
        int left(const int i) const {return i * 2 + 1;}
        int right(const int i) const {return i * 2 + 2;}

        void heapify(const int);
        void insert_node(struct HuffmanNode*);
        struct HuffmanNode* extract_min();
        int get_HeapSize() const {return HeapSize;}
        struct HuffmanNode* get_root() const {return *nodes;}
    protected:

    private:
        int HeapSize;
        int capacity;
        struct HuffmanNode **nodes;
};

#endif
