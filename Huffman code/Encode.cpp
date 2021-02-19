#include "Encode.hpp"


//initialize -FileRead- and -FileWrite- and start encode
Encode::Encode(const char *R):
    FileRead(R)
{
    string W = R;
    int s = W.size();
    char FileW[s + 2];
    for(int i = 0; i < s; i++)
        FileW[i] = W[i];
    FileW[s] = FileW[s + 1] = '\0';
    int index = strlen(FileW);
    while(FileW[index] != '.')
    {
        FileW[index] = FileW[index - 1];
        index--;
    }
    FileW[index] = '-';
    FileWrite = FileW;
    encoding();
}

//check file --> build tree --> encode
void Encode::encoding()
{
    //check -FileRead-
    FILE *FileR = fopen(FileRead, "r");
    if(FileR == NULL)
    {
        cout << "fail to open " << FileRead << endl;
        return;
    }
    char ch;
    if(fscanf(FileR, "%c", &ch) == EOF)
    {
        cout << FileRead << " is empty" << endl;
        return;
    }
    fclose(FileR);

    //build Huffman tree, and insert into -Huffman_table-
    build_tree();

    //encode

    FileR = fopen(FileRead, "r");
    FILE *FileW = fopen(FileWrite, "w");
    //file print Huffman Tree
    map<char, string>::iterator it;
    for(it = Huffman_table.begin(); it != Huffman_table.end(); it++)
    {
        fprintf(FileW, "%c", it->first);
        string code = it->second;
        for(int i = 0; i < code.size(); i++)
            fprintf(FileW, "%c", code[i]);
        fprintf(FileW, "%c", ' ');
    }

    fprintf(FileW, "%s", "  ");

    //file print code
    string code = "";
    // 215^4 < 2^31 < 216^4
    while(fscanf(FileR, "%c", &ch) != EOF)
    {
        code += Huffman_table[ch];
        while(code.size() >= 31)
        {
            string f31c = "";//first 31 code
            string rc = "";//remain code
            for(int i = 0; i < code.size(); i++)
            {
                if(i < 31)
                    f31c += code[i];
                else
                    rc += code[i];
            }
            int num = 0;
            for(int i = 0; i < 31; i++)
                num = num * 2 + (f31c[i] - '0');
            char p[4];//print
            for(int i = 0; i < 4; i++)
            {
                p[4 - i - 1] = num % 216;
                num /= 216;
            }
            //(char)26 = ^z
            for(int i = 0; i < 4; i++)
                fprintf(FileW, "%c", p[i] + 27);//27~242
            code = rc;
        }
    }

    //last code
    if(code.size() != 0)
    {
        int cs = code.size();//code size
        while(code.size() < 31)
            code += '0';
        int n = 0;
        for(int i = 0; i < 31; i++)
            n = n * 2 + (code[i] - '0');
        char p[4];
        for(int i = 0; i < 4; i++)
        {
            p[4 - i - 1] = n % 216;
            n /= 216;
        }

        for(int i = 0; i < 4; i++)
            fprintf(FileW, "%c", p[i] + 27);
        for(int i = 0; i < 31 - cs; i++)
            fprintf(FileW, "%c", 243);
    }

    fclose(FileR);
    fclose(FileW);

}

//get character count --> build min heap --> build Huffman Tree -->
//assign code --> build table
void Encode::build_tree()
{
    get_count();


    //insert -char_counts- into -min_heap-
    Heap min_heap;
    map<char, int>::iterator it;
    for(it = char_counts.begin(); it != char_counts.end(); it++)
    {
        struct HuffmanNode *new_node = new struct HuffmanNode;
        new_node->key = it->first;
        new_node->cou = it->second;
        min_heap.insert_node(new_node);
    }

    //build Huffman tree
    while(min_heap.get_HeapSize() > 1)
    {
        struct HuffmanNode *node = new struct HuffmanNode;
        node->left = min_heap.extract_min();
        node->right = min_heap.extract_min();
        node->cou = node->left->cou + node->right->cou;
        min_heap.insert_node(node);
    }

    //assign -code- to the member in the Huffman tree
    if(min_heap.get_root()->left == NULL && min_heap.get_root()->right == NULL)
        min_heap.get_root()->code += '0';
    else
        assign_code(min_heap.get_root());

    build_table(min_heap.get_root());
}

//get character count with the given file name(-FileRead-)
//put counts in -map<char, int> char_counts-
void Encode::get_count()
{
    FILE *FileR = fopen(FileRead, "r");
    char ch;
    fscanf(FileR, "%c", &ch);
    while(true)
    {
        if(char_counts.find(ch) == char_counts.end())
        {
            char_counts.insert(pair<char, int>(ch, 1));
        }
        else
            char_counts[ch]++;
        if(fscanf(FileR, "%c", &ch) == EOF) break;
    }
    fclose(FileR);
}

//<<recursion>> assign -code- to the left node and the right node of the given node
void Encode::assign_code(struct HuffmanNode *node)
{
    if(node->left != NULL)
    {
        node->left->code = node->code + '0';
        assign_code(node->left);
    }
    if(node->right != NULL)
    {
        node->right->code = node->code + '1';
        assign_code(node->right);
    }
}

//<<recursion>> insert -key- and -code- of the leaf node into -Huffman_table-
void Encode::build_table(struct HuffmanNode *node)
{
    if(node->left == NULL && node->right == NULL)
    {
        Huffman_table.insert(pair<char, string>(node->key, node->code));
        return;
    }
    build_table(node->left);
    build_table(node->right);
}



