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
            void writeSOSMarker();
    };
}

#endif
