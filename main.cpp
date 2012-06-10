#include <iostream>
#include <utility>
#include <vector>

#include "BMP.h"
#include "PixelsTransform.h"
#include "RGBPixel.h"
#include "YUVPixel.h"
#include "JPEG.h"
#include "utils.h"
#include "HuffmanTable.h"

using namespace std;
using namespace Compression;


int main(){
    BMP* bmp;
    bmp = BMP::readImage("test.bmp");
    RGBPixelSet set = bmp->getRGBPixelSet();
    JPEG jpg(&set);
    jpg.writeJPEG("test.jpg");


    return 0;
}

