#include <iostream>
#include <utility>
#include <vector>

#include "BMP.h"
#include "PixelsTransform.h"
#include "RGBPixel.h"
#include "YUVPixel.h"
#include "JPEG.h"
#include "utils.h"
#include "HuffmanTree.h"
#include "HuffmanTable.h"

using namespace std;
using namespace Compression;


int main(){
    BMP* bmp;
    bmp = BMP::readImage("test.bmp");
    RGBPixelSet set = bmp->getRGBPixelSet();
    JPEG jpg(&set);
    jpg.writeJPEG("test.jpg");

    int n = 3;
    int ns[]{1,1,1};
    int vs[]{1,2,3};
    HuffmanTable ht(n, ns, vs);
    HuffmanTree htr(&ht);

    return 0;
}

