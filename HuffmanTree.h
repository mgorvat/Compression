#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <vector>

using namespace std;

class HuffmanTree{
    public:
        HuffmanTree();
        HuffmanTree(vector<int>* path, HuffmanTree* parent);
        ~HuffmanTree();
        HuffmanTree* getLeft();
        HuffmanTree* getRight();
        HuffmanTree* getParent();
        vector<int>* getPath();
        HuffmanTree* addVal(int length, int val);
        int getVal();
        bool haveVal();
    private:
        vector<int>* path;
        int val;
        HuffmanTree* left;
        HuffmanTree* right;
        HuffmanTree* parent;
};
#endif
