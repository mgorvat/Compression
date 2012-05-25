#include "Utils.h"

vector<pair<int, int> >* zeroSeqCodind(int seq[64]){
    int ind = 1, ct = 0;
    int zerBlocks = 0;
    vector<pair<int, int> > *res = new vector<pair<int, int> >();
    while(ind < 64){
        if(seq[ind] == 0) ct++;
        else{
            while(zerBlocks > 0){
                res->push_back(pair<int, int> (0, 15));
                zerBlocks--;
            }
            res->push_back(pair<int, int> (seq[ind], ct));
            ct = 0;
        }
        if(ct == 15){zerBlocks++; ct = 0;}
        ind++;
    }
    if(ct != 0)res->push_back(pair<int, int> (0, 0));
    return res;
}

void writeAC(pair<int, int> code, CodeWriter* writer, HuffmanCoder<pair<int, int> >* coder){
    if(code == pair<int, int>(0, 0)){writer->writeCode(coder->getCode(&code)); return; }
    if(code == pair<int, int>(0, 15)){writer->writeCode(coder->getCode(&code)); return; }
    pair<int, int> buf;
    pair<int, int> RZ = getCode(code.first);
    buf = pair<int, int>(RZ.first, code.second);
    buf = coder->getCode(&buf);
    writer->writeCode(buf);
    writer->writeCode(RZ);
}

pair<int, int> getCode(int numb){
    if(numb == 0)return pair<int, int>(0, 0);
    int buf = numb>0? numb: -numb;
    int size = 0;
    while(buf > 0){
        size++;
        buf = buf>>1;
    }
    if(size == 16)return pair<int, int> (16, 0);
    buf = 1<<size;
    int code;
    if(numb<0){
        buf = -buf;
        buf++;
        code = numb - buf;
    }else code = numb;
    return pair<int, int> (size, code);
}

pair<int, int> getUnaryCode(int length){
    if(length == 16)return pair<int, int>(16, 0xFF);
    int res = 0;
    for(int i = 0; i < length; i++) res = (res<<1) + 1;
    res = res<<1;
    return pair<int, int>(length + 1, res);
}


void encodeDC(int numb, CodeWriter* writer, HuffmanCoder<int>* DCcoder){
    pair<int, int> p = getCode(numb);
    int buf = p.first;
    pair<int, int> p2 = DCcoder->getCode(&buf);
    writer->writeCode(p2);
    writer->writeCode(p);
}

int* toIntMtr(float mtr[64]){
    int* res = new int[64];
    for(int i = 0; i < 64; i++) res[i] = (int)(mtr[i] + 0.5);
    return res;
}

int encodeMatrix(float mtr[64], CodeWriter* writer, HuffmanCoder<pair<int, int> >* ACcoder,
                  HuffmanCoder<int>* DCcoder, int prevDc){
    encodeDC(mtr[0] - prevDc, writer, DCcoder);
    int* iMtr = toIntMtr(mtr);
    vector<pair<int, int> > * vec = zeroSeqCodind(iMtr);
    for(int i = 0; i < vec->size(); i++){
        writeAC((*vec)[i], writer, ACcoder);
    }
    delete iMtr;
    return mtr[0];
}


vector<int>* numbers(vector<pair<pair<int, int>, int> >* table){
    vector<int>* res = new vector<int>();
    int length = 1;
    int ct = 0;

    for(int i = 0; i < table->size(); i++){
        if((*table)[i].first.first == length) ct++;
        else{
            res->push_back(ct);
            length++;
            ct = 0;
            i--;
        }
    }
    if(ct != 0)res->push_back(ct);
    return res;
}
