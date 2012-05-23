#ifndef TREESTREAMER_H_INCLUDED
#define TREESTREAMER_H_INCLUDED

#include "HuffmanTree.h"

class TreeStreamer{
    public:
        TreeStreamer(HuffmanTree* tree);
        int* getVal(int nextBit);
    private:
        HuffmanTree* treeRoot;
        HuffmanTree* curNode;
};
#endif
