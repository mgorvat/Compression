#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <vector>
#include <utility>

#include "CodeWriter.h"
#include "HuffmanEncoder.h"
#include "JPEG.h"

using namespace std;

vector<pair<int, int> >* seqCodind(int seq[64]);
pair<int, int> getCode(int numb);
pair<int, int> getUnaryCode(int length);
int* toIntMtr(float mtr[64]);
vector<pair<int, int> >* zeroSeqCodind(int seq[64]);
vector<int>* numbers(vector<pair<pair<int, int>, int> >*);

#endif // UTILS_H_INCLUDED
