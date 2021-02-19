#include <iostream>
#include <map>
#include <string.h>
#include "Encode.hpp"
#include "Decode.hpp"

using namespace std;

int main()
{
    int n;
    bool break_loop = false;
    cout << "input 1 to compress, input 2 to decompress, input 0 to exit\n: ";
    while(cin >> n)
    {
        int s;
        switch(n)
        {
        case 0:
            break_loop = true;
            break;
        case 1:
            {
                cout << "\n\n-----compress file-----\n\n";
                cout << "file name: ";
                string compress_file;
                cin >> compress_file;
                s = compress_file.size();
                char compressF[s + 1];
                for(int i = 0; i < s; i++)
                    compressF[i] = compress_file[i];
                compressF[s] = '\0';
                Encode enc(compressF);
                break;
            }
        case 2:
            {
                cout << "\n\n-----decompress file-----\n\n";
                cout << "file name: ";
                string decompress_file;
                cin >> decompress_file;
                s = decompress_file.size();
                char decompressF[s + 1];
                for(int i = 0; i < s; i++)
                    decompressF[i] = decompress_file[i];
                decompressF[s] = '\0';
                Decode dec(decompressF);
                break;
            }
        }
        if(break_loop) break;

        cout << "\n\ninput 1 to compress, input 2 to decompress, input 0 to exit\n: ";
    }



    return 0;

}
