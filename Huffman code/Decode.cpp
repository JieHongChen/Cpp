#include "Decode.hpp"
#include <stack>

Decode::Decode(const char *R):
    FileRead(R)
{
    string W = FileRead;
    int s = W.size();
    char FileW[s + 2];
    for(int i = 0; i < s; i++)
        FileW[i] = W[i];
    FileW[s] = FileW[s + 1] = '\0';
    int index = s;
    while(FileW[index] != '.')
    {
        FileW[index] = FileW[index - 1];
        index--;
    }
    FileW[index] = '+';

    FileWrite = FileW;

    decoding();

}

//check file --> get table --> decode
void Decode::decoding()
{
    //check -FileRead-
    FILE *FileR = fopen(FileRead, "r");
    if(FileR == NULL)
    {
        cout << "fail to open file " << FileRead << endl;
        return;
    }
    char ch;
    if(fscanf(FileR, "%c", &ch) == EOF)
    {
        cout << FileRead << " is empty" << endl;
        return;
    }
    fclose(FileR);

    //decode
    FileR = fopen(FileRead, "r");
    FILE *FileW = fopen(FileWrite, "w");


    bool break_loop = false;
    //build -Huffman_table-
    while(true)
    {
        fscanf(FileR, "%c", &ch);
        char key = ch;
        string code;
        while(true)
        {
            fscanf(FileR, "%c", &ch);
            if(ch == ' ')
            {
                if(code.size() == 0)
                {
                    break_loop = true;
                    break;
                }
                Huffman_table.insert(pair<string, char>(code, key));
                code = "";
                break;
            }
            else
                code += ch;
        }
        if(break_loop) break;
    }

    //file print
    FileW = fopen(FileWrite, "w");
    string code = "";
    break_loop = false;
    fscanf(FileR, "%c", &ch);//first codee
    while(true)
    {
        int n = 0, x = 0;
        for(int i = 0; i < 4; i++)
        {
            n = n * 216 + (((int)ch - 27 + 256) % 256);
            if(fscanf(FileR, "%c", &ch) == EOF)//next code
                break_loop = true;
            if(((int)ch - 27 + 256) % 256 == 216)
            {
                do
                {
                    x++;
                }while(fscanf(FileR, "%c", &ch) != EOF);
            }
        }
        stack<char> binary;
        for(int i = 0; i < 31; i++)
        {
            binary.push((n % 2) + '0');
            n /= 2;
        }
        for(int i = 0; i < 31 - x; i++)
        {
            code += binary.top();
            if(Huffman_table.find(code) != Huffman_table.end())
            {
                fprintf(FileW, "%c", Huffman_table[code]);
                code = "";
            }
            binary.pop();
        }
        if(break_loop || x) break;
    }

    fclose(FileR);
    fclose(FileW);
}

