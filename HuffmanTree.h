#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "HuffmanTable.h"

using namespace std;

class HuffmanTree{
    public:
        HuffmanTree(HuffmanTable* ht);
        ~HuffmanTree();
        HuffmanEncoder<int> makeEncoder();
    private:
        HuffmanTree();
        HuffmanTree(int codeLength, int codeVal, HuffmanTree* parent);
        HuffmanTree* getLeft();
        HuffmanTree* getRight();
        HuffmanTree* getParent();
        int getVal();
        bool haveVal();
        HuffmanTree* addVal(int length, int val);


        int val;
        HuffmanTree* left;
        HuffmanTree* right;
        HuffmanTree* parent;
        int codeLength;
        int codeVal;

};
#endif
