#include "BMP.h"

//TODO: Rewrite it with no warnings

namespace Compression{
    BMP* BMP::readImage(string fileName){
        //BMP *ret = new BMP();
//        long imSize, width, height;
//        unsigned short bitCount;
//        unsigned long compr, clrUsed, clrImp;
//        long xRes, yRes;
        /*Buffers for reading file.*/

        ifstream in;

        in.open(fileName.c_str(), ifstream::binary);//Opening of the file.
        BMPInfo *inf = new BMPInfo();
        in>>(*inf);

        if(inf->imagSize == 0) inf->imagSize = inf->width * inf->height * inf->bitCount;
        RGBPixelSet *rgb;
        if(inf->bitCount == 24) rgb = read24BitImage(&in, inf->height, inf->width);

        BMP *bmp = new BMP();

        in.close();
        bmp->inf = inf;
        bmp->pixels = rgb;
        return bmp;
    }

    void BMP::writeBMP(string fileName){
        ofstream out;
        out.open(fileName.c_str(), std::ios::binary);
        out<<hex;
        out<<*(this->inf);
        if(this->inf->bitCount == 24){
            write24BitImage(out);
        }
        out.close();
    }

    /**
        Reading pixels of image. Must be called after reading the header.
        @input:
            in — input stream.
            line — number of lines in the image.
            columns - number of columns in the image.
        @output:
            RGBPixelSet structure appropriate with image.
    */
    RGBPixelSet* BMP::read24BitImage(istream* in, int lines, int columns){
        RGBPixelSet *rgb = new RGBPixelSet(lines, columns);
        for(int i = 0; i < lines; i++){
            for(int j = 0; j < columns; j++){
                RGBPixel px;
                (*in)>>px;
                rgb->addPixel(px);
            }
        }
        return rgb;
    }

    void BMP::write24BitImage(ostream& out){
        for(int i = 0; i < (this->pixels)->getHeight(); i++){
            for(int j = 0; j < (this->pixels)->getWidth(); j++){
                RGBPixel *px = pixels->getPixel(i,j);
                out<<(*px);
            }
        }
    }

    RGBPixelSet BMP::getRGBPixelSet(){
        return (*pixels);
    }
}
