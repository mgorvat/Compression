#include "HuffmanTable.h"
#include "JPEGConstants.h"

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
    if(a.first.first != b.first.first) return a.first.first < b.first.first;
    return a.first.second < b.first.second;
}



HuffmanCoder<int>* initDCCoder(int index){
    vector<pair<pair<int, int>, int> > *vec;

    if(index == 0)vec = dcHuffTable(0);
    else vec = dcHuffTable(1);

    vector<int> *vals = new vector<int>();
    vector<pair<int, int> > *codes = new vector<pair<int, int> >();
    for(int i = 0; i < (int)vec->size(); i++){
        vals->push_back((*vec)[i].second);
        codes->push_back((*vec)[i].first);
    }
    HuffmanCoder<int>* res = new HuffmanCoder<int>(vals, codes);
    delete vals;
    delete codes;
    delete vec;
    return res;
}

HuffmanCoder<int>* initCoder(int index){
    pair<int, int>* codeTable;
    pair<int, int> eof;
    pair<int, int> zrl;
    if(index == 0){
        codeTable = (pair<int, int>*)&lht;
        eof = leof;
        zrl = lzrl;
    }
    else {
        codeTable = (pair<int, int>*)&cht;
        eof = ceof;
        zrl = czrl;
    }
    vector <int> vals;
    vector <pair<int, int> > codes;
    codes.push_back(eof); vals.push_back(0);
    codes.push_back(zrl); vals.push_back(15<<4);
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 16; j++){
            vals.push_back((j<<4) + i + 1);
            codes.push_back(codeTable[10 * j + i]);
        }
    }
    HuffmanCoder<int>* coder = new HuffmanCoder<int>(&vals, &codes);
    return coder;
}

vector<pair<pair<int, int>, int> >* makeJPEGTable(int index){
    pair<int, int>* codeTable;
    pair<int, int> eof;
    pair<int, int> zrl;
    if(index == 0){
        codeTable = (pair<int, int>*)&lht;
        eof = leof;
        zrl = lzrl;
    }
    else {
        codeTable = (pair<int, int>*)&cht;
        eof = ceof;
        zrl = czrl;
    }
    vector<pair<pair<int, int>, int> >* vec = new vector<pair<pair<int, int>, int> >();
    vec->push_back(pair<pair<int, int>, int>(eof, 0));
    vec->push_back(pair<pair<int, int>, int>(zrl, 0xf0));



    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 16; j++){
            vec->push_back(pair<pair<int, int>, int>(codeTable[10 * j + i], (j<<4) + i + 1));
        }
    }
    sort(vec->begin(), vec->end(), comp);



    return vec;
}


vector<pair<pair<int, int> ,int> >* dcHuffTable(int n){
    vector<pair<pair<int, int> ,int> > *res = new vector<pair<pair<int, int> ,int> > ();
    if(n == 0){
        pair<int, int> p(2, 0);
        res->push_back(pair<pair<int, int>, int>(p, 0));
        p = pair<int, int> (3, 2);
        res->push_back(pair<pair<int, int>, int>(p, 1));
        p = pair<int, int> (3, 3);
        res->push_back(pair<pair<int, int>, int>(p, 2));
        p = pair<int, int> (3, 4);
        res->push_back(pair<pair<int, int>, int>(p, 3));
        p = pair<int, int> (3, 5);
        res->push_back(pair<pair<int, int>, int>(p, 4));
        p = pair<int, int> (3, 6);
        res->push_back(pair<pair<int, int>, int>(p, 5));
        p = pair<int, int> (4, 14);
        res->push_back(pair<pair<int, int>, int>(p, 6));
        p = pair<int, int> (5, 30);
        res->push_back(pair<pair<int, int>, int>(p, 7));
        p = pair<int, int> (6, 62);
        res->push_back(pair<pair<int, int>, int>(p, 8));
        p = pair<int, int> (7, 126);
        res->push_back(pair<pair<int, int>, int>(p, 9));
        p = pair<int, int> (8, 254);
        res->push_back(pair<pair<int, int>, int>(p, 10));
        p = pair<int, int> (9, 510);
        res->push_back(pair<pair<int, int>, int>(p, 11));
    }else{
        pair<int, int> p(2, 0);
        res->push_back(pair<pair<int, int>, int>(p, 0));
        p = pair<int, int> (2, 1);
        res->push_back(pair<pair<int, int>, int>(p, 1));
        p = pair<int, int> (2, 2);
        res->push_back(pair<pair<int, int>, int>(p, 2));
        p = pair<int, int> (3, 6);
        res->push_back(pair<pair<int, int>, int>(p, 3));
        p = pair<int, int> (4, 14);
        res->push_back(pair<pair<int, int>, int>(p, 4));
        p = pair<int, int> (5, 30);
        res->push_back(pair<pair<int, int>, int>(p, 5));
        p = pair<int, int> (6, 62);
        res->push_back(pair<pair<int, int>, int>(p, 6));
        p = pair<int, int> (7, 126);
        res->push_back(pair<pair<int, int>, int>(p, 7));
        p = pair<int, int> (8, 254);
        res->push_back(pair<pair<int, int>, int>(p, 8));
        p = pair<int, int> (9, 510);
        res->push_back(pair<pair<int, int>, int>(p, 9));
        p = pair<int, int> (10, 1022);
        res->push_back(pair<pair<int, int>, int>(p, 10));
        p = pair<int, int> (11, 2046);
        res->push_back(pair<pair<int, int>, int>(p, 11));
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
