#include "HuffmanTree.h"

//TODO: Comment this
//TODO: Make error handlers

HuffmanTree::HuffmanTree(): left(0), right(0), parent(0), code(){}
HuffmanTree::HuffmanTree(Code code, HuffmanTree* parent):
                        left(0), right(0), parent(parent), code(code){}
HuffmanTree::HuffmanTree(HuffmanTable* ht): left(0), right(0), parent(0), code(){
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

HuffmanEncoder<int>* HuffmanTree::makeEncoder(){
    vector<Code> codes;
    vector<int> vals;
    makeEncoder(this, &codes, &vals);
    HuffmanEncoder<int> *enc = new HuffmanEncoder<int>(&vals, &codes);
    return enc;
}

void HuffmanTree::makeEncoder(HuffmanTree* ht, vector<Code>* codes, vector<int>* vals){
    if(ht->haveVal()){
        codes->push_back(ht->code);
        vals->push_back(ht->getVal());
    }else{
        if(ht->left != 0) makeEncoder(ht->left, codes, vals);
        if(ht->right != 0) makeEncoder(ht->right, codes, vals);
    }
}


int HuffmanTree::getVal(){return val;}
bool HuffmanTree::haveVal(){return ((left == 0) & (right == 0));}

HuffmanTree* HuffmanTree::addVal(int length, int val){
    if(length > code.length){
        if(left == 0){
            int nextVal = (code.value<<1) ^ 0;
            int nextLength = code.length + 1;
            Code c(nextLength, nextVal);
            HuffmanTree* nd = new HuffmanTree(c, this);
            left = nd;
            return left->addVal(length, val);
        }
        if(right == 0){
            int nextVal = (code.value<<1) ^ 1;
            int nextLength = code.length + 1;
            Code c(nextLength, nextVal);
            HuffmanTree* nd = new HuffmanTree(c, this);
            right = nd;
            return right->addVal(length, val);
        }
        return parent->addVal(length, val);
    }else{
        this->val = val;
        return parent;
    }
}

