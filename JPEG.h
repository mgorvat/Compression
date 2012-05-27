#ifndef JPEG_H_INCLUDED
#define JPEG_H_INCLUDED

#include <cstdlib>
#include <fstream>
#include <vector>

#include "RGBPixelSet.h"
#include "YUVPixelSet.h"
#include "PixelsTransform.h"
#include "Utils.h"
#include "HuffmanTable.h"
#include "DCT.h"

using namespace std;

namespace Compression{
    struct ComponentInfo{
        ComponentInfo(char id, char dcTable, char acTable): id(id), dcTable(dcTable), acTable(acTable){}
        char id;
        char dcTable;
        char acTable;
    };

    struct ComponentsEncoders{
        ComponentsEncoders(HuffmanCoder<int>* dcEncoder,
                          HuffmanCoder<int>* acEncoder): dcEncoder(dcEncoder), acEncoder(acEncoder) {}
        ~ComponentsEncoders(){
            delete dcEncoder;
            delete acEncoder;
        }
        HuffmanCoder<int>* dcEncoder;
        HuffmanCoder<int>* acEncoder;
    };

    class JPEG{
        public:
            JPEG(RGBPixelSet *pxs);
            ~JPEG();
            void writeJPEG(string filename);
            vector<char> getComment();
            void setComment(vector<char> com);
        private:
            YUVPixelSet *yuvSet;
            int matrixCountInWidth, matrixCountInHeight;
            float **YWorkMatrix, **CrWorkMatrix, **CbWorkMatrix;
            float **YDCTMatrix, **CrDCTMatrix, **CbDCTMatrix;
            vector<char> comment;

            void separateComponents();
            float** initMatrix();
            void computeDCT();
            void quantify();
            void writeComment(ofstream* out);
            void writeQuantanizationTable(ofstream* out, char identificator, int table[64]);
            void writeSOF0Marker(ofstream* out, char precision, char numberOfComponents);
            char* generateSOF0ComponentInfo(char id, char verticalSampling,
                char horizontalSampling, char quantTableIndex);
            void writeDHTMarker(ofstream* out, char htNumber, char htType, vector<pair<pair<int, int>, int> >* codes);
            void writeSOSMarker(ofstream* out, vector<ComponentInfo>* components);
            int encodeMatrix(float* mtr, CodeWriter* writer, ComponentsEncoders* encoders, int prevDc);
            void encodeDC(int numb, CodeWriter* writer, HuffmanCoder<int>* DCcoder);
            void writeAC(int code, CodeWriter* writer, HuffmanCoder<int>* coder);
    };
}

#endif
