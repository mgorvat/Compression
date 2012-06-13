#include "HuffmanTree.h"

//TODO: Comment this
//TODO: Make error handlers

HuffmanTree::HuffmanTree(): left(0), right(0), parent(0), codeLength(0), codeVal(0){}
HuffmanTree::HuffmanTree(int codeLength, int codeVal, HuffmanTree* parent):
                        left(0), right(0), parent(parent), codeLength(codeLength), codeVal(codeVal){}
HuffmanTree::HuffmanTree(HuffmanTable* ht): left(0), right(0), parent(0), codeLength(0), codeVal(0){
    HuffmanTree* cur = this;
    int ind = 0;
    for(int i = 0; i < ht->n; i++){
        for(int j = 0; j < ht->numbers[i]; j++){
            cur = cur->addVal(i+1, ht->values[ind++]);
        }
    }
}

HuffmanTree::~HuffmanTree(){
    delete left;
    delete right;
}

//HuffmanEncoder<int> makeEncoder(){
//    return 0;
//}

HuffmanTree* HuffmanTree::getLeft(){return left;}
HuffmanTree* HuffmanTree::getRight(){return right;}
HuffmanTree* HuffmanTree::getParent(){return parent;}
int HuffmanTree::getVal(){return val;}
bool HuffmanTree::haveVal(){return ((left == 0) & (right == 0));}

HuffmanTree* HuffmanTree::addVal(int length, int val){
    if(length > codeLength){
        if(left == 0){
            int nextVal = (codeVal<<1) ^ 0;
            int nextLength = codeLength + 1;
            HuffmanTree* nd = new HuffmanTree(nextLength, nextVal, this);
            left = nd;
            return left->addVal(length, val);
        }
        if(right == 0){
            int nextVal = (codeVal<<1) ^ 1;
            int nextLength = codeLength + 1;
            HuffmanTree* nd = new HuffmanTree(nextLength, nextVal, this);
            left = nd;
            return left->addVal(length, val);
        }
        return parent->addVal(length, val);
    }else{
        this->val = val;
        return parent;
    }
}

