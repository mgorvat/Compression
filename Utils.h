#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <vector>
#include <utility>

#include "CodeWriter.h"
#include "HuffmanEncoder.h"
#include "JPEG.h"

using namespace std;

vector<pair<int, int> >* seqCodind(int seq[64]);
Code getCode(int numb);
Code getUnaryCode(int length);
int* toIntMtr(float mtr[64]);
vector<pair<int, int> >* zeroSeqCodind(int seq[64]);
vector<int>* numbers(vector<pair<Code, int> >*);

#endif // UTILS_H_INCLUDED
