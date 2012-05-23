#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(): left(0), right(0){
    path = new vector<int>();

}
HuffmanTree::HuffmanTree(vector<int>* path, HuffmanTree* parent): path(path), left(0), right(0), parent(parent){}

HuffmanTree::~HuffmanTree(){
    delete left;
    delete right;
    delete path;
}

HuffmanTree* HuffmanTree::getLeft(){
    return left;
}

HuffmanTree* HuffmanTree::getRight(){
    return right;
}

HuffmanTree* HuffmanTree::getParent(){
    return parent;
}

vector<int>* HuffmanTree::getPath(){
    return path;
}

HuffmanTree* HuffmanTree::addVal(int length, int val){
    if(length > path->size()){
        if(left == 0){
            vector<int>* pth = new vector<int>(path->begin(), path->end());
            pth->push_back(0);
            HuffmanTree* nd = new HuffmanTree(pth, this);
            left = nd;
            return left->addVal(length, val);
        }
        if(right == 0){
            vector<int>* pth = new vector<int>(path->begin(), path->end());
            pth->push_back(1);
            HuffmanTree* nd = new HuffmanTree(pth, this);
            right = nd;
            return right->addVal(length, val);
        }
        return parent->addVal(length, val);
    }
    this->val = val;
    return parent;
}
int HuffmanTree::getVal(){return val;}

bool HuffmanTree::haveVal(){
    return ((left == 0) & (right == 0));
}
