#include "JPEG.h"

//luminosity quantanization table
int lqt[]{2, 1, 1, 2, 3, 5, 6, 7,
          1, 1, 2, 2, 3, 7, 7, 7,
          2, 2, 2, 3, 5, 7, 8, 7,
          2, 2, 3, 3, 6, 10, 10, 7,
          2, 3, 4, 7, 8, 13, 12, 9,
          3, 4, 7, 8, 10, 12, 14, 11,
          6, 8, 9, 10, 12, 15, 14, 12,
          9, 11, 11, 12, 13, 12, 12, 12};
int lqtz[64];



//chromaticity quantanization table
int cqt[]{2, 2, 3, 6, 12, 12, 12, 12,
          2, 3, 3, 8, 12, 12, 12, 12,
          3, 3, 7, 12, 12, 12, 12, 12,
          6, 8, 12, 12, 12, 12, 12, 12,
          12, 12, 12, 12, 12, 12, 12, 12,
          12, 12, 12, 12, 12, 12, 12, 12,
          12, 12, 12, 12, 12, 12, 12, 12,
          12, 12, 12, 12, 12, 12, 12, 12};
int cqtz[64];

using namespace Compression;


//TODO: Comment this
//TODO: Think about memory leaks

char* invert(char* numb, int size){
    char* res = (char*)malloc(size);
    for(int i = 0; i < size; i++) res[i] = numb[size - i - 1];
    return res;
}

void writeInvert(ofstream* out, char* numb, int size){
    out->write(invert(numb, size), size);
}


void zigzag(int* matr, int* imatr){
    char buf;
    bool up = true;
    int ct = 0;
    for(int i = 0; i < 8; i++){
        if(up){
            for(int j = 0; j <= i; j++){
                buf = (char)matr[8 * (i - j) + j];
                imatr[ct++] = buf;
            }
        }else{
            for(int j = i; j >= 0; j--){
                buf = (char)matr[8 * (i - j) + j];
                imatr[ct++] = buf;
            }
        }
        up = !up;
    }
    for(int i = 7; i >= 0; i--){
        if(up){
            for(int j = 0; j < i; j++){
                buf = (char)matr[8 * (7 - j) +  8 - i + j];
                imatr[ct++] = buf;
            }
        }
        else{
            for(int j = 0; j < i; j++){
                buf = (char)matr[8 * (8 - i + j) + 7 - j];
                imatr[ct++] = buf;
            }
        }
        up=!up;
    }
}

JPEG::JPEG(RGBPixelSet *pxs){
    yuvSet = RGBSetToYUVSet(pxs);
    zigzag(lqt, lqtz); zigzag(cqt, cqtz);
    separateComponents();
    computeDCT();
    quantify();
}

JPEG::~JPEG(){
    delete yuvSet;
    delete[] YWorkMatrix;
    delete[] CrWorkMatrix;
    delete[] CbWorkMatrix;
}

vector<char> JPEG::getComment(){
    return comment;
}

void JPEG::setComment(vector<char> com){
    comment = com;
}

void JPEG::separateComponents(){
    matrixCountInWidth = yuvSet->getWidth() / 8 + !(!(yuvSet->getWidth() % 8));
    matrixCountInHeight = yuvSet->getHeight() / 8 + !(!(yuvSet->getHeight() % 8));
    YWorkMatrix = initMatrix(); CrWorkMatrix = initMatrix(); CbWorkMatrix = initMatrix();
    YDCTMatrix = initMatrix(); CrDCTMatrix = initMatrix(); CbDCTMatrix = initMatrix();

    for(int i = 0; i < matrixCountInWidth; i++){
        for(int j = 0; j < matrixCountInHeight; j++){
            for(int l = 0; l < 8; l++){
                for(int k = 0; k < 8; k++){
                    YWorkMatrix[i*matrixCountInWidth+j][8*l+k] = yuvSet->getPixel(8*i+l, 8*j+k)->Y;
                    CrWorkMatrix[i*matrixCountInWidth+j][8*l+k] = yuvSet->getPixel(8*i+l, 8*j+k)->Cr;
                    CbWorkMatrix[i*matrixCountInWidth+j][8*l+k] = yuvSet->getPixel(8*i+l, 8*j+k)->Cb;
                }
            }
        }
    }
    if(yuvSet->getWidth() % 8){
        for(int i = 1; i <= matrixCountInHeight; i++){
            for(int j = 0; j < yuvSet->getWidth() % 8; j++){
                for(int k = 0; k < 8; k++){
                    YWorkMatrix[i*matrixCountInWidth - 1][8 * k + yuvSet->getWidth() % 8 + j] =
                        YWorkMatrix[i*matrixCountInWidth - 1][8 * k + yuvSet->getWidth() % 8 + j - 1];
                    CrWorkMatrix[i*matrixCountInWidth - 1][8 * k + yuvSet->getWidth() % 8 + j] =
                        CrWorkMatrix[i*matrixCountInWidth - 1][8 * k + yuvSet->getWidth() % 8 + j - 1];
                    CbWorkMatrix[i*matrixCountInWidth - 1][8 * k + yuvSet->getWidth() % 8 + j] =
                        CbWorkMatrix[i*matrixCountInWidth - 1][8 * k + yuvSet->getWidth() % 8 + j - 1];
                }

            }
        }
    }
}

float** JPEG::initMatrix(){
    float** mtr = (float**)malloc(matrixCountInWidth * matrixCountInHeight * sizeof(float*));
    for(int i = 0; i < matrixCountInWidth * matrixCountInHeight; i++){
        mtr[i] = (float*)malloc(64 * sizeof(float));
    }
    return mtr;
}


void JPEG::computeDCT(){
    for(int i = 0; i < matrixCountInWidth * matrixCountInHeight; i++){
        YDCTMatrix[i] = DCT(YWorkMatrix[i]);
        CrDCTMatrix[i] = DCT(CrWorkMatrix[i]);
        CbDCTMatrix[i] = DCT(CbWorkMatrix[i]);
    }
}

void JPEG::quantify(){
    for(int i = 0; i < matrixCountInWidth * matrixCountInHeight; i++){
        for(int j = 0; j < 64; j++){
            YDCTMatrix[i][j] = YDCTMatrix[i][j] / lqt[j];
            CrDCTMatrix[i][j] = CrDCTMatrix[i][j] / cqt[j];
            CbDCTMatrix[i][j] = CbDCTMatrix[i][j] / cqt[j];
        }
    }

}

void JPEG::writeJPEG(string filename){
    ofstream out;
    out.open(filename.c_str(), std::ios::binary);

    unsigned short wBuf;
    char cBuf;
    wBuf = 0xffd8;
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));

    writeComment(&out);
    writeQuantanizationTable(&out, (char)0, lqtz);//Writing luminosity quantanization table
    writeQuantanizationTable(&out, (char)1, cqtz);//Writing chromaticity quantanization table
    writeSOF0Marker(&out, 8, 3);
    //Number of components can't be changet yet. What is precision I don't understand. Usually it is 8.

    vector<pair<pair<int, int>, int> >* codes;

    //Writing of 4 DCT markers. It can be better. Fix it.
    codes = dcHuffTable(0); writeDHTMarker(&out, 0, 0, codes); delete codes;
    codes = makeJPEGTable(0); writeDHTMarker(&out, 0, 1, codes); delete codes;
    codes = dcHuffTable(1); writeDHTMarker(&out, 1, 0, codes); delete codes;
    codes = makeJPEGTable(1); writeDHTMarker(&out, 1, 1, codes); delete codes;

    wBuf = 0xffda;
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    wBuf = 12;
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    cBuf = 3;
    out.write(&cBuf, sizeof(cBuf));
    cBuf = 1;//Y
    out.write(&cBuf, sizeof(cBuf));
    cBuf = 0x00;
    out.write(&cBuf, sizeof(cBuf));

    cBuf = 2;//Cb
    out.write(&cBuf, sizeof(cBuf));
    cBuf = 0x11;
    out.write(&cBuf, sizeof(cBuf));

    cBuf = 3;//Cr
    out.write(&cBuf, sizeof(cBuf));
    cBuf = 0x11;
    out.write(&cBuf, sizeof(cBuf));

    cBuf = 0;
    out.write(&cBuf, sizeof(cBuf));
    cBuf = 0x3f;
    out.write(&cBuf, sizeof(cBuf));
    cBuf = 0;
    out.write(&cBuf, sizeof(cBuf));//Three ignorable bytes

    CodeWriter writer(out);
    HuffmanCoder<pair<int, int> >* lCoder = initCoder(0);
    HuffmanCoder<pair<int, int> >* cCoder = initCoder(1);
    HuffmanCoder<int>* lDCCoder = initDCCoder(0);
    HuffmanCoder<int>* cDCCoder = initDCCoder(1);


    int prevY = 512, prevCb = 512, prevCr = 512;
    for(int i = matrixCountInHeight - 1; i >= 0; i--){
        for(int j = 0; j < matrixCountInWidth; j++){
            prevY = encodeMatrix(YDCTMatrix[i * matrixCountInWidth + j], &writer, lCoder, lDCCoder, prevY);
            prevCb = encodeMatrix(CbDCTMatrix[i * matrixCountInWidth + j], &writer, cCoder, cDCCoder, prevCb);
            prevCr = encodeMatrix(CrDCTMatrix[i * matrixCountInWidth + j], &writer, cCoder, cDCCoder, prevCr);

        }
    }
    writer.flush();


    wBuf = 0xffd9;
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    out.close();
}

void JPEG::writeComment(ofstream *out){
    if(comment.size() > 0){
        unsigned short wBuf = 0xfffe;
        out->write(invert((char*)&wBuf, sizeof(wBuf)), sizeof(wBuf));
        short size = comment.size() + 2;
        writeInvert(out, (char*)&size, sizeof(size));
        for(int i = 0; i < comment.size(); i++)out->write(&comment[i], sizeof(char));
    }
}

void JPEG::writeQuantanizationTable(ofstream* out, char identificator, int table[64]){
    unsigned short wBuf = 0xffdb;
    char cBuf;
    writeInvert(out, (char*)&wBuf, sizeof(wBuf));
    //Writing DQT marker

    wBuf = 0x0043;//Size of marker
    writeInvert(out, (char*)&wBuf, sizeof(wBuf));//Writing size of marker
    out->write(&identificator, sizeof(identificator));
    for(int i = 0; i < 64; i++){
        cBuf = (char)table[i];
        out->write(&cBuf, sizeof(char));
    }
}

void JPEG::writeSOF0Marker(ofstream* out, char precision, char numberOfComponents){
    unsigned short wBuf = 0xffc0;
    writeInvert(out, (char*)&wBuf, sizeof(wBuf));
    wBuf = 17;//Marker size. It's value is 17 for 3 components
    writeInvert(out, (char*)&wBuf, sizeof(wBuf));
    out->write(&precision, sizeof(precision));
    wBuf = yuvSet->getWidth();
    writeInvert(out, (char*)&wBuf, sizeof(wBuf));
    wBuf = yuvSet->getHeight();
    writeInvert(out, (char*)&wBuf, sizeof(wBuf));
    //Writing height and width of image
    out->write(&numberOfComponents, sizeof(numberOfComponents));

    char* ComponentInfo;
    /*
        For componrnts info. Now only 3 components JPEGs are availible and for
        samping only value 1 can be used. Should be fixed later.
    */
    int horizontalSampling[]{1, 1, 1};
    int verticalSampling[]{1, 1, 1};
    int quantTable[]{0, 1, 1};//Methods for controlling this not supported yet. It's temporary solution.
    for(int i = 0; i < numberOfComponents; i++){
        ComponentInfo = generateSOF0ComponentInfo(i+1, horizontalSampling[i],
            verticalSampling[i], quantTable[i]);
        for(int j = 0; j < 3; j++)
            out->write(&ComponentInfo[j], sizeof(ComponentInfo[j]));
        delete ComponentInfo;
    }
}

char* JPEG::generateSOF0ComponentInfo(char id,
        char horizontalSampling, char verticalSampling, char quantTableIndex){
    char *res = new char[3];
    res[0] = id;
    res[1] = (horizontalSampling<<4) + verticalSampling;
    res[2] = quantTableIndex;
    return res;
}


void JPEG::writeDHTMarker(ofstream* out, char htNumber, char htType, vector<pair<pair<int, int>, int> >* codes){
    unsigned short wBuf = 0xffc4;
    writeInvert(out, (char*)&wBuf, sizeof(wBuf));
    wBuf = 19 + codes->size();//Size of marker. Equals 19 + number of codes.
    writeInvert(out, (char*)&wBuf, sizeof(wBuf));

    char cBuf = htNumber + (htType<<4);//Byte for HT information
    out->write(&cBuf, sizeof(char));
    vector<int>* numbs = numbers(codes);//Number of elements for each code length
    for(int i = 0; i < 16; i++){//Writing code lenghtes
        if(i < numbs->size()) cBuf = (*numbs)[i];
        else cBuf = 0;
        out->write(&cBuf, sizeof(cBuf));
    }
    for(int i = 0; i < codes->size(); i++){//Writing code values
        cBuf = (*codes)[i].second;
        out->write(&cBuf, sizeof(cBuf));
    }
    delete numbs;
}


void JPEG::writeSOSMarker(){

}
