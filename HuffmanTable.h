#ifndef HUFFMANTABLE_H_INCLUDED
#define HUFFMANTABLE_H_INCLUDED

#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>


#include "HuffmanEncoder.h"

using namespace std;

HuffmanEncoder<int>* initCoder(int);
HuffmanEncoder<int>* initDCCoder(int);
vector<pair<pair<int, int>, int> >* makeJPEGTable(int index);
vector<pair<pair<int, int>, int> >* dcHuffTable(int n);
vector<int>* dcNumbs();

#endif // HUFFMANTABLE_H_INCLUDED
