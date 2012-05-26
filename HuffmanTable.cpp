#include "HuffmanTable.h"

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
    if(a.first.first != b.first.first) return a.first.first < b.first.first;
    return a.first.second < b.first.second;
}


pair<int, int> leof = pair<int, int>(4, 10);
pair<int, int> lzrl = pair<int, int>(11, 2041);
pair<int, int>lht[]{
      pair<int, int>(2, 0), pair<int, int>(2, 1), pair<int, int>(3, 4), pair<int, int>(4, 11), pair<int, int>(5, 26),
      pair<int, int>(7, 120), pair<int, int>(8, 248), pair<int, int>(10, 1014), pair<int, int>(16, 65410), pair<int, int>(16, 65411),
      pair<int, int>(4, 12), pair<int, int>(5, 27), pair<int, int>(7, 121), pair<int, int>(9, 502), pair<int, int>(11, 2038),
      pair<int, int>(16, 65412), pair<int, int>(16, 65413), pair<int, int>(16, 65414), pair<int, int>(16, 65415), pair<int, int>(16, 65416),
      pair<int, int>(5, 28), pair<int, int>(8, 249), pair<int, int>(10, 1015), pair<int, int>(12, 4084), pair<int, int>(16, 65417),
      pair<int, int>(16, 65418), pair<int, int>(16, 65419), pair<int, int>(16, 65420), pair<int, int>(16, 65421), pair<int, int>(16, 65422),
      pair<int, int>(6, 58), pair<int, int>(9, 503), pair<int, int>(12, 4085), pair<int, int>(16, 65423), pair<int, int>(16, 65424),
      pair<int, int>(16, 65425), pair<int, int>(16, 65426), pair<int, int>(16, 65427), pair<int, int>(16, 65428), pair<int, int>(16, 65429),
      pair<int, int>(6, 59), pair<int, int>(10, 1016), pair<int, int>(16, 65430), pair<int, int>(16, 65431), pair<int, int>(16, 65432),
      pair<int, int>(16, 65433), pair<int, int>(16, 65434), pair<int, int>(16, 65435), pair<int, int>(16, 65436), pair<int, int>(16, 65437),
      pair<int, int>(7, 122), pair<int, int>(11, 2039), pair<int, int>(16, 65438), pair<int, int>(16, 65439), pair<int, int>(16, 65440),
      pair<int, int>(16, 65441), pair<int, int>(16, 65442), pair<int, int>(16, 65443), pair<int, int>(16, 65444), pair<int, int>(16, 65445),
      pair<int, int>(7, 123), pair<int, int>(12, 4086), pair<int, int>(16, 65446), pair<int, int>(16, 65447), pair<int, int>(16, 65448),
      pair<int, int>(16, 65449), pair<int, int>(16, 65450), pair<int, int>(16, 65451), pair<int, int>(16, 65452), pair<int, int>(16, 65453),
      pair<int, int>(8, 250), pair<int, int>(12, 4087), pair<int, int>(16, 65454), pair<int, int>(16, 65455), pair<int, int>(16, 65456),
      pair<int, int>(16, 65457), pair<int, int>(16, 65458), pair<int, int>(16, 65459), pair<int, int>(16, 65460), pair<int, int>(16, 65461),
      pair<int, int>(9, 504), pair<int, int>(15, 32704), pair<int, int>(16, 65462), pair<int, int>(16, 65463), pair<int, int>(16, 65464),
      pair<int, int>(16, 65465), pair<int, int>(16, 65466), pair<int, int>(16, 65467), pair<int, int>(16, 65468), pair<int, int>(16, 65469),
        pair<int, int>(9, 505), pair<int, int>(16, 65470), pair<int, int>(16, 65471), pair<int, int>(16, 65472), pair<int, int>(16, 65473),
      pair<int, int>(16, 65474), pair<int, int>(16, 65475), pair<int, int>(16, 65476), pair<int, int>(16, 65477), pair<int, int>(16, 65478),
      pair<int, int>(9, 506), pair<int, int>(16, 65479), pair<int, int>(16, 65480), pair<int, int>(16, 65481), pair<int, int>(16, 65482),
      pair<int, int>(16, 65483), pair<int, int>(16, 65484), pair<int, int>(16, 65485), pair<int, int>(16, 65486), pair<int, int>(16, 65487),
      pair<int, int>(10, 1017), pair<int, int>(16, 65488), pair<int, int>(16, 65489), pair<int, int>(16, 65490), pair<int, int>(16, 65491),
      pair<int, int>(16, 65492), pair<int, int>(16, 65493), pair<int, int>(16, 65494), pair<int, int>(16, 65495), pair<int, int>(16, 65496),
      pair<int, int>(10, 1018), pair<int, int>(16, 65497), pair<int, int>(16, 65498), pair<int, int>(16, 65499), pair<int, int>(16, 65500),
      pair<int, int>(16, 65501), pair<int, int>(16, 65502), pair<int, int>(16, 65503), pair<int, int>(16, 65504), pair<int, int>(16, 65505),
      pair<int, int>(11, 2040), pair<int, int>(16, 65506), pair<int, int>(16, 65507), pair<int, int>(16, 65508), pair<int, int>(16, 65509),
      pair<int, int>(16, 65510), pair<int, int>(16, 65511), pair<int, int>(16, 65512), pair<int, int>(16, 65513), pair<int, int>(16, 65514),
      pair<int, int>(16, 65515), pair<int, int>(16, 65516), pair<int, int>(16, 65517), pair<int, int>(16, 65518), pair<int, int>(16, 65519),
      pair<int, int>(16, 65520), pair<int, int>(16, 65521), pair<int, int>(16, 65522), pair<int, int>(16, 65523), pair<int, int>(16, 65524),
      pair<int, int>(16, 65525), pair<int, int>(16, 65526), pair<int, int>(16, 65527), pair<int, int>(16, 65528), pair<int, int>(16, 65529),
      pair<int, int>(16, 65530), pair<int, int>(16, 65531), pair<int, int>(16, 65532), pair<int, int>(16, 65533), pair<int, int>(16, 65534)
};


pair<int, int> ceof = pair<int, int>(2, 0);
pair<int, int> czrl = pair<int, int>(10, 1018);
pair<int, int> cht[]{
      pair<int, int>(2, 1), pair<int, int>(3, 4), pair<int, int>(4, 10), pair<int, int>(5, 24), pair<int, int>(5, 25),
      pair<int, int>(6, 56), pair<int, int>(7, 120), pair<int, int>(9, 500), pair<int, int>(10, 1014), pair<int, int>(12, 4084),
      pair<int, int>(4, 11), pair<int, int>(6, 57), pair<int, int>(8, 246), pair<int,int>(9, 501), pair<int, int>(11, 2038),
      pair<int, int>(12, 4085), pair<int, int>(16, 65416), pair<int, int>(16, 65417), pair<int, int>(16, 65418), pair<int, int>(16, 65419),
      pair<int, int>(5, 26), pair<int, int>(8, 247), pair<int, int>(10, 1015), pair<int, int>(12, 4086), pair<int, int>(15, 32706),
      pair<int, int>(16, 65420), pair<int, int>(16, 65421), pair<int, int>(16, 65422), pair<int, int>(16, 65423), pair<int, int>(16, 65424),
      pair<int, int>(5, 27), pair<int, int>(8, 248), pair<int, int>(10, 1016), pair<int, int>(12, 4087), pair<int, int>(16, 65425),
      pair<int, int>(16, 65426), pair<int, int>(16, 65427), pair<int, int>(16, 65428), pair<int, int>(16, 65429), pair<int, int>(16, 65430),
      pair<int, int>(6, 58), pair<int, int>(9, 502), pair<int, int>(16, 65431), pair<int, int>(16, 65432), pair<int, int>(16, 65433),
      pair<int, int>(16, 65434), pair<int, int>(16, 65435), pair<int, int>(16, 65436), pair<int, int>(16, 65437), pair<int, int>(16, 65438),
      pair<int, int>(6, 59), pair<int, int>(10, 1017), pair<int, int>(16, 65439), pair<int, int>(16, 65440), pair<int, int>(16, 65441),
      pair<int, int>(16, 65442), pair<int, int>(16, 65443), pair<int, int>(16, 65444), pair<int, int>(16, 65445), pair<int, int>(16, 65446),
      pair<int, int>(7, 121), pair<int, int>(11, 2039), pair<int, int>(16, 65447), pair<int, int>(16, 65448), pair<int, int>(16, 65449),
      pair<int, int>(16, 65450), pair<int, int>(16, 65451), pair<int, int>(16, 65452), pair<int, int>(16, 65453), pair<int, int>(16, 65454),
      pair<int, int>(7, 122), pair<int, int>(11, 2040), pair<int, int>(16, 65455), pair<int, int>(16, 65456), pair<int, int>(16, 65457),
      pair<int, int>(16, 65458), pair<int, int>(16, 65459), pair<int, int>(16, 65460), pair<int, int>(16, 65461), pair<int, int>(16, 65462),
      pair<int, int>(8, 249), pair<int, int>(16, 65463), pair<int, int>(16, 65464),pair<int, int>(16, 65465), pair<int, int>(16, 65466),
      pair<int, int>(16, 65467), pair<int, int>(16, 65468), pair<int, int>(16, 65469), pair<int, int>(16, 65470), pair<int, int>(16, 65471),
      pair<int, int>(9, 503), pair<int, int>(16, 65472), pair<int, int>(16, 65473),pair<int, int>(16, 65474), pair<int, int>(16, 65475),
      pair<int, int>(16, 65476), pair<int, int>(16, 65477), pair<int, int>(16, 65478), pair<int, int>(16, 65479), pair<int, int>(16, 65480),
      pair<int, int>(9, 504), pair<int, int>(16, 65481), pair<int, int>(16, 65482), pair<int, int>(16, 65483), pair<int, int>(16, 65484),
      pair<int, int>(16, 65485), pair<int, int>(16, 65486), pair<int, int>(16, 65487), pair<int, int>(16, 65488), pair<int, int>(16, 65489),
      pair<int, int>(9, 505), pair<int, int>(16, 65490), pair<int, int>(16, 65491), pair<int, int>(16, 65492), pair<int, int>(16, 65493),
      pair<int, int>(16, 65494), pair<int, int>(16, 65495), pair<int, int>(16, 65496), pair<int, int>(16, 65497), pair<int, int>(16, 65498),
      pair<int, int>(9, 506), pair<int, int>(16, 65499), pair<int, int>(16, 65500), pair<int, int>(16, 65501), pair<int, int>(16, 65502),
      pair<int, int>(16, 65503), pair<int, int>(16, 65504), pair<int, int>(16, 65505), pair<int, int>(16, 65506), pair<int, int>(16, 65507),
      pair<int, int>(11, 2041), pair<int, int>(16, 65508), pair<int, int>(16, 65509), pair<int, int>(16, 65510), pair<int, int>(16, 65511),
      pair<int, int>(16, 65512), pair<int, int>(16, 65513), pair<int, int>(16, 65514), pair<int, int>(16, 65515), pair<int, int>(16, 65516),
      pair<int, int>(14, 16352), pair<int, int>(16, 65517), pair<int, int>(16, 65518), pair<int, int>(16, 65519), pair<int, int>(16, 65520),
      pair<int, int>(16, 65521), pair<int, int>(16, 65522), pair<int, int>(16, 65523), pair<int, int>(16, 65524), pair<int, int>(16, 65525),
      pair<int, int>(15, 32707), pair<int, int>(16, 65526), pair<int, int>(16, 65527), pair<int, int>(16, 65528), pair<int, int>(16, 65529),
      pair<int, int>(16, 65530), pair<int, int>(16, 65531), pair<int, int>(16, 65532), pair<int, int>(16, 65533), pair<int, int>(16, 65534)
};

HuffmanCoder<int>* initDCCoder(int index){
    vector<pair<pair<int, int>, int> > *vec;

    if(index == 0)vec = dcHuffTable(0);
    else vec = dcHuffTable(1);

    vector<int> *vals = new vector<int>();
    vector<pair<int, int> > *codes = new vector<pair<int, int> >();
    for(int i = 0; i < vec->size(); i++){
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
