#ifndef HUFFMANTABLE_H_INCLUDED
#define HUFFMANTABLE_H_INCLUDED

#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>

#include "JPEGConstants.h"
#include "HuffmanEncoder.h"


using namespace std;

class HuffmanTree;

class HuffmanTable{
    friend HuffmanTree;
    public:
        HuffmanTable(int n, int* numbs, int* vals): n(n), numbers(numbs), values(vals){}
    private:
        int n;
        int* numbers;
        int* values;
};

HuffmanEncoder<int>* initCoder(int);
HuffmanEncoder<int>* initDCCoder(int);
vector<pair<Code, int> >* makeJPEGTable(int index);
vector<pair<Code, int> >* dcHuffTable(int n);
vector<int>* dcNumbs();

#endif // HUFFMANTABLE_H_INCLUDED
