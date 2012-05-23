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
int lqti[64];



//chromaticity quantanization table
int cqt[]{2, 2, 3, 6, 12, 12, 12, 12,
          2, 3, 3, 8, 12, 12, 12, 12,
          3, 3, 7, 12, 12, 12, 12, 12,
          6, 8, 12, 12, 12, 12, 12, 12,
          12, 12, 12, 12, 12, 12, 12, 12,
          12, 12, 12, 12, 12, 12, 12, 12,
          12, 12, 12, 12, 12, 12, 12, 12,
          12, 12, 12, 12, 12, 12, 12, 12};
int cqti[64];

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
    zigzag(lqt, lqti); zigzag(cqt, cqti);
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

    if(comment.size() > 0){
        wBuf = 0xfffe;
        out.write(invert((char*)&wBuf, sizeof(wBuf)), sizeof(wBuf));
        short size = comment.size() + 2;
        writeInvert(&out, (char*)&size, sizeof(size));
        for(int i = 0; i < comment.size(); i++)out.write(&comment[i], sizeof(char));
    }

    //Writing luminosity quantanization table
    wBuf = 0xffdb;
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    //Writing DQT marker

    wBuf = 0x0043;//Size of marker
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));//Writing size of marker
    cBuf = 0;//One byte size, 0 identificator
    out.write(&cBuf, sizeof(cBuf));
    for(int i = 0; i < 64; i++){
        cBuf = (char)lqti[i];
        out.write(&cBuf, sizeof(char));
    }
    //Writing chromaticity quantanization table
    wBuf = 0xffdb;
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    //Writing DQT marker

    wBuf = 0x0043;//Size of marker
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));//Writing size of marker
    cBuf = 1;//One byte size, 1 identificator
    out.write(&cBuf, sizeof(cBuf));
    for(int i = 0; i < 64; i++){
        cBuf = (char)cqti[i];
        out.write(&cBuf, sizeof(char));
    }

    //Writing SOF0 marker
    wBuf = 0xffc0;
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    wBuf = 17;//Marker size. Now we have only one possyble value
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    cBuf = 8;//Data precision
    out.write(&cBuf, sizeof(cBuf));
    wBuf = yuvSet->getWidth();
//    wBuf = 16;
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    wBuf = yuvSet->getHeight();
//    wBuf = 16;
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    //Writing height and width of image
    cBuf = 3;//Writing number of components
    out.write(&cBuf, sizeof(cBuf));

    cBuf = 1;
    out.write(&cBuf, sizeof(cBuf));
    cBuf = (1<<4) + 1;
    out.write(&cBuf, sizeof(cBuf));
    cBuf = 0;
    out.write(&cBuf, sizeof(cBuf));

    cBuf = 2;
    out.write(&cBuf, sizeof(cBuf));
    cBuf = (1<<4) + 1;
    out.write(&cBuf, sizeof(cBuf));
    cBuf = 1;
    out.write(&cBuf, sizeof(cBuf));

    cBuf = 3;
    out.write(&cBuf, sizeof(cBuf));
    cBuf = (1<<4) + 1;
    out.write(&cBuf, sizeof(cBuf));
    cBuf = 1;
    out.write(&cBuf, sizeof(cBuf));

    //DHT marker. DC table
    wBuf = 0xffc4;
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    wBuf = 31;
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    cBuf = 0x00;//HT information
    out.write(&cBuf, sizeof(cBuf));
    vector<pair<pair<int, int>, int> >* dcTable = dcHuffTable(0);
    vector<int>* numbs = numbers(dcTable);
    for(int i = 0; i < 16; i++){
        if(i < numbs->size()) cBuf = (*numbs)[i];
        else cBuf = 0;
        out.write(&cBuf, sizeof(cBuf));
    }
    for(int i = 0; i < dcTable->size(); i++){
        cBuf = (*dcTable)[i].second;
        out.write(&cBuf, sizeof(cBuf));
    }
    delete numbs;
    delete dcTable;

    //DHT marker. Luminosity AC table.
    wBuf = 0xffc4;
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    wBuf = 181;//Size. 181 for AC
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    cBuf = 0x10;//HT information
    out.write(&cBuf, sizeof(cBuf));
    vector<pair<pair<int, int>, int> >* table;
    table = makeJPEGTable(0);
    numbs = numbers(table);
    for(int i = 0; i < 16; i++){
        if(i < numbs->size()) cBuf = (*numbs)[i];
        else cBuf = 0;
        out.write(&cBuf, sizeof(cBuf));
    }
    for(int i = 0; i < table->size(); i++){
        cBuf = (*table)[i].second;
        out.write(&cBuf, sizeof(cBuf));
    }
    delete table;
    delete numbs;



    //DHT marker. DC table
    wBuf = 0xffc4;
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    wBuf = 31;
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    cBuf = 0x01;//HT information
    out.write(&cBuf, sizeof(cBuf));
    dcTable = dcHuffTable(1);
    numbs = numbers(dcTable);
    for(int i = 0; i < 16; i++){
        if(i < numbs->size()) cBuf = (*numbs)[i];
        else cBuf = 0;
        out.write(&cBuf, sizeof(cBuf));
    }
    for(int i = 0; i < dcTable->size(); i++){
        cBuf = (*dcTable)[i].second;
        out.write(&cBuf, sizeof(cBuf));
    }
    delete numbs;
    delete dcTable;




    //DHT marker. Chrominance AC table.
    wBuf = 0xffc4;
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    wBuf = 181;//Size. 181 for AC
    writeInvert(&out, (char*)&wBuf, sizeof(wBuf));
    cBuf = 0x11;//HT information
    out.write(&cBuf, sizeof(cBuf));
    table = makeJPEGTable(1);
    numbs = numbers(table);
    for(int i = 0; i < 16; i++){
        if(i < numbs->size()) cBuf = (*numbs)[i];
        else cBuf = 0;
        out.write(&cBuf, sizeof(cBuf));
    }
    for(int i = 0; i < table->size(); i ++){
        cBuf = (*table)[i].second;
        out.write(&cBuf, sizeof(cBuf));
    }
    delete table;
    delete numbs;


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
