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
//    string input, inputFile, outputFile;
//    BMP* bmp;
//    while(true){
//        cin>>input;
//        if(input == "compress"){
//            bmp = BMP::readImage("test.bmp");
//            RGBPixelSet set = bmp->getRGBPixelSet();
//            cin>>inputFile>>outputFile;
//            JPEG jpg(&set);
//            jpg.writeJPEG("test.jpg");
//            cout<<"File was compressed successfully\n";
//        }
//        else{
//            if(input == "exit")return 0;
//            else cout<<"Unknown command.\n";
//        }
//    }


    BMP* bmp;
    bmp = BMP::readImage("test.bmp");
    RGBPixelSet set = bmp->getRGBPixelSet();
    JPEG jpg(&set);
    jpg.writeJPEG("test.jpg");


    return 0;
}

