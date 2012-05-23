#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <vector>
#include <utility>

#include "CodeWriter.h"
#include "HuffmanCoder.h"

using namespace std;

vector<pair<int, int> >* seqCodind(int seq[64]);
void writeAC(pair<int, int> code, CodeWriter* writer, HuffmanCoder<pair<int, int> >* coder);
pair<int, int> getCode(int numb);
pair<int, int> getUnaryCode(int length);
int encodeMatrix(float mtr[64], CodeWriter* writer, HuffmanCoder<pair<int, int> >* ACcoder,
                  HuffmanCoder<int>* DCcoder, int prevDc);
vector<int>* numbers(vector<pair<pair<int, int>, int> >*);

#endif // UTILS_H_INCLUDED
