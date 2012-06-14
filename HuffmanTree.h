#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <vector>

#include "HuffmanTable.h"
#include "HuffmanEncoder.h"

using namespace std;

class HuffmanTree{
    public:
        HuffmanTree(HuffmanTable* ht);
        ~HuffmanTree();
        HuffmanEncoder<int>* makeEncoder();
    private:
        HuffmanTree();
        HuffmanTree(Code code, HuffmanTree* parent);
        static void makeEncoder(HuffmanTree* ht, vector<Code>* codes, vector<int>* vals);
        int getVal();
        bool haveVal();
        HuffmanTree* addVal(int length, int val);


        int val;
        HuffmanTree* left;
        HuffmanTree* right;
        HuffmanTree* parent;
        Code code;

};
#endif
