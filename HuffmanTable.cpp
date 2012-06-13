#include "HuffmanTable.h"


bool comp(pair<Code, int> a, pair<Code, int> b) {
    if(a.first.length != b.first.length) return a.first.length < b.first.length;
    return a.first.value < b.first.value;
}



HuffmanEncoder<int>* initDCCoder(int index){
    vector<pair<Code, int> > *vec;

    if(index == 0)vec = dcHuffTable(0);
    else vec = dcHuffTable(1);

    vector<int> *vals = new vector<int>();
    vector<Code> *codes = new vector<Code>();
    for(int i = 0; i < (int)vec->size(); i++){
        vals->push_back((*vec)[i].second);
        codes->push_back((*vec)[i].first);
    }
    HuffmanEncoder<int>* res = new HuffmanEncoder<int>(vals, codes);
    delete vals;
    delete codes;
    delete vec;
    return res;
}

HuffmanEncoder<int>* initCoder(int index){
    Code* codeTable;
    Code eof;
    Code zrl;
    if(index == 0){
        codeTable = (Code*)&lht;
        eof = leof;
        zrl = lzrl;
    }
    else {
        codeTable = (Code*)&cht;
        eof = ceof;
        zrl = czrl;
    }
    vector <int> vals;
    vector <Code > codes;
    codes.push_back(eof); vals.push_back(0);
    codes.push_back(zrl); vals.push_back(15<<4);
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 16; j++){
            vals.push_back((j<<4) + i + 1);
            codes.push_back(codeTable[10 * j + i]);
        }
    }
    HuffmanEncoder<int>* coder = new HuffmanEncoder<int>(&vals, &codes);
    return coder;
}

vector<pair<Code, int> >* makeJPEGTable(int index){
    Code* codeTable;
    Code eof;
    Code zrl;
    if(index == 0){
        codeTable = (Code*)&lht;
        eof = leof;
        zrl = lzrl;
    }
    else {
        codeTable = (Code*)&cht;
        eof = ceof;
        zrl = czrl;
    }
    vector<pair<Code, int> >* vec = new vector<pair<Code, int> >();
    vec->push_back(pair<Code, int>(eof, 0));
    vec->push_back(pair<Code, int>(zrl, 0xf0));



    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 16; j++){
            vec->push_back(pair<Code, int>(codeTable[10 * j + i], (j<<4) + i + 1));
        }
    }
    sort(vec->begin(), vec->end(), comp);



    return vec;
}


vector<pair<Code ,int> >* dcHuffTable(int n){
    vector<pair<Code ,int> > *res = new vector<pair<Code ,int> > ();
    if(n == 0){
        Code p(2, 0);
        res->push_back(pair<Code, int>(p, 0));
        p = Code (3, 2);
        res->push_back(pair<Code, int>(p, 1));
        p = Code (3, 3);
        res->push_back(pair<Code, int>(p, 2));
        p = Code (3, 4);
        res->push_back(pair<Code, int>(p, 3));
        p = Code (3, 5);
        res->push_back(pair<Code, int>(p, 4));
        p = Code (3, 6);
        res->push_back(pair<Code, int>(p, 5));
        p = Code (4, 14);
        res->push_back(pair<Code, int>(p, 6));
        p = Code (5, 30);
        res->push_back(pair<Code, int>(p, 7));
        p = Code (6, 62);
        res->push_back(pair<Code, int>(p, 8));
        p = Code (7, 126);
        res->push_back(pair<Code, int>(p, 9));
        p = Code (8, 254);
        res->push_back(pair<Code, int>(p, 10));
        p = Code (9, 510);
        res->push_back(pair<Code, int>(p, 11));
    }else{
        Code p(2, 0);
        res->push_back(pair<Code, int>(p, 0));
        p = Code (2, 1);
        res->push_back(pair<Code, int>(p, 1));
        p = Code (2, 2);
        res->push_back(pair<Code, int>(p, 2));
        p = Code (3, 6);
        res->push_back(pair<Code, int>(p, 3));
        p = Code (4, 14);
        res->push_back(pair<Code, int>(p, 4));
        p = Code (5, 30);
        res->push_back(pair<Code, int>(p, 5));
        p = Code (6, 62);
        res->push_back(pair<Code, int>(p, 6));
        p = Code (7, 126);
        res->push_back(pair<Code, int>(p, 7));
        p = Code (8, 254);
        res->push_back(pair<Code, int>(p, 8));
        p = Code (9, 510);
        res->push_back(pair<Code, int>(p, 9));
        p = Code (10, 1022);
        res->push_back(pair<Code, int>(p, 10));
        p = Code (11, 2046);
        res->push_back(pair<Code, int>(p, 11));
    }
    return res;
}

vector<int>* dcNumbs(){
    vector<int> *res = new vector<int>();
    res->push_back(1);
    res->push_back(1);
    res->push_back(1);
    res->push_back(1);
    res->push_back(1);
    res->push_back(1);
    res->push_back(1);
    res->push_back(1);
    res->push_back(1);
    res->push_back(1);
    res->push_back(1);
    res->push_back(1);
    res->push_back(1);
    res->push_back(1);
    res->push_back(1);
    res->push_back(2);
    return res;
}
