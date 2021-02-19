#ifndef DECODE_HPP
#define DECODE_HPP
#include <iostream>
#include <map>
#include <string.h>

using namespace std;

class Decode
{
    public:
        Decode(const char*);
        void decoding();

    protected:

    private:
        const char *FileRead;
        const char *FileWrite;
        map<string, char> Huffman_table;
};

#endif
