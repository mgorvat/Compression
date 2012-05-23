#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED

#include <fstream>

using namespace std;

#include "BMPInfo.h"
#include "RGBPixel.h"
#include "RGBPixelSet.h"


namespace Compression{
    class BMP{
        public:
            static BMP* readImage(string fileName);
            void writeBMP(string fileName);
            RGBPixelSet getRGBPixelSet();
        protected:
            BMPInfo *inf;
            RGBPixelSet *pixels;
        private:
            static RGBPixelSet* read24BitImage(istream* in, int lines, int columns);
            void write24BitImage(ostream& out);
    };
}

#endif
