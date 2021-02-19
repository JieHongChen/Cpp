#ifndef ENCODE_HPP
#define ENCODE_HPP
#include <iostream>
#include <map>
#include <string.h>
#include "Heap.hpp"

using namespace std;

class Encode
{
    public:
        //initialize -FileRead- and -FileWrite-
        Encode(const char*);

        //encode the given file(-FileRead-) and put the result in -FileWrite-
        void encoding();

        //build the huffman tree and insert into -Huffman_table-
        void build_tree();

        //get character count of the given file(-FileRead-) and put in -char_counts-
        void get_count();

        //<<recursion>> assign code to the left node and the right node of the given node
        void assign_code(struct HuffmanNode*);

        //<<recursion>> insert the -key- and -code- of the leaf node into -Huffman_table-
        void build_table(struct HuffmanNode*);

    protected:

    private:
        const char *FileRead;
        const char *FileWrite;
        map<char, int> char_counts;
        map<char, string> Huffman_table;
};

#endif
