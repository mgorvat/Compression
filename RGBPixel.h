#ifndef RGBPIXEL_H_INCLUDED
#define RGBPIXEL_H_INCLUDED

#include <fstream>
#include <iostream>

using namespace std;
namespace Compression{
    struct RGBPixel{
        //TODO : Comment this
        float red;
        float green;
        float blue;

        RGBPixel(){}
        RGBPixel(unsigned char red, unsigned char green, unsigned char blue): red(red), green(green), blue(blue){}

        friend istream& operator>>(istream& in, RGBPixel& px){
            unsigned char rBuf, gBuf, bBuf;
            in.read(reinterpret_cast<char*>(&bBuf), sizeof(unsigned char)); px.blue = bBuf;
            in.read(reinterpret_cast<char*>(&gBuf), sizeof(unsigned char)); px.green = gBuf;
            in.read(reinterpret_cast<char*>(&rBuf), sizeof(unsigned char)); px.red = rBuf;
            return in;
        }

        friend ostream& operator<<(ostream& out, RGBPixel& px){
            unsigned char r = (unsigned char)(px.red + 0.5),
                g = (unsigned char)(px.green + 0.5),
                b = (unsigned char)(px.blue + 0.5);
            out.write(reinterpret_cast<char*>(&b), sizeof(b));
            out.write(reinterpret_cast<char*>(&g), sizeof(g));
            out.write(reinterpret_cast<char*>(&r), sizeof(r));
            return out;
        }

    };
}
#endif
