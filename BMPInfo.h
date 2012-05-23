#include <fstream>

using namespace std;

struct BMPInfo{
    unsigned long fSize;
    long width;
    long height;
    unsigned long byteOffset;
    unsigned short bitCount;
    unsigned long compr;
    unsigned long imagSize;
    long xRes;
    long yRes;
    unsigned long clrUsed;
    unsigned long clrImp;


    friend ostream& operator<<(ostream& out, BMPInfo& inf){
        unsigned short wBuf;
        unsigned long dBuf;
        wBuf = 0x4d42;
        out.write(reinterpret_cast<char*>(&wBuf), sizeof(wBuf));//Writing "BM"
        out.write(reinterpret_cast<char*>(&inf.fSize), sizeof(fSize));//Writing file size
        wBuf = 0;
        out.write(reinterpret_cast<char*>(&wBuf), sizeof(wBuf));
        out.write(reinterpret_cast<char*>(&wBuf), sizeof(wBuf));//Writing reserved values
        out.write(reinterpret_cast<char*>(&inf.byteOffset), sizeof(inf.byteOffset));//Writing byte offset
        dBuf = 0x28;
        out.write(reinterpret_cast<char*>(&dBuf), sizeof(dBuf));//Writing structure size
        out.write(reinterpret_cast<char*>(&inf.width), sizeof(inf.width));
        out.write(reinterpret_cast<char*>(&inf.height), sizeof(inf.height));//Writing image height and width
        wBuf = 0x1;
        out.write(reinterpret_cast<char*>(&wBuf), sizeof(wBuf));//Writing number of planes
        out.write(reinterpret_cast<char*>(&inf.bitCount), sizeof(inf.bitCount));//Writing number of planes
        out.write(reinterpret_cast<char*>(&inf.compr), sizeof(inf.compr));//Writing compression type
        out.write(reinterpret_cast<char*>(&inf.imagSize), sizeof(inf.imagSize));//Writing of the image size
        out.write(reinterpret_cast<char*>(&inf.xRes), sizeof(inf.xRes));
        out.write(reinterpret_cast<char*>(&inf.yRes), sizeof(inf.yRes));//Writing of the resolutions
        out.write(reinterpret_cast<char*>(&inf.clrUsed), sizeof(inf.clrUsed));//Writing of the number of the using colors
        out.write(reinterpret_cast<char*>(&inf.clrImp), sizeof(inf.clrImp));//Writing of the number of important indexes

        return out;
    }


    friend istream& operator>>(istream& in, BMPInfo& inf){
        //TODO: Make something while error.
        unsigned short wBuf;
        unsigned long dBuf;
        long lBuf;

        in.read(reinterpret_cast<char*>(&wBuf), sizeof(wBuf));//Reading of the file type.

        if(wBuf != 0x4D42){return in;}//It's not BMP! Must be 0x4D42.


        in.read(reinterpret_cast<char*>(&dBuf), sizeof(dBuf));//Reading of the file size. Actuall I don't know how it use.
        inf.fSize = dBuf;

        //TODO: Insert checking of the file size here


        in.read(reinterpret_cast<char*>(&wBuf), sizeof(wBuf));
        in.read(reinterpret_cast <char*>(&wBuf), sizeof(wBuf));//Reading of the two reserved values. Their value is ignoring.


        in.read(reinterpret_cast<char*>(&dBuf), sizeof(dBuf));//Reading of the byte offset. Actually I don't know how to use it.
        inf.byteOffset = dBuf;

        in.read(reinterpret_cast<char*>(&dBuf), sizeof(dBuf));//Size of the structure. Must be 0x28.
        if(dBuf != 0x28){return in;}//Error. Must be 0x28.


        in.read(reinterpret_cast<char*>(&lBuf), sizeof(lBuf));
        inf.width = lBuf;

        in.read(reinterpret_cast<char*>(&lBuf), sizeof(lBuf));
        inf.height = lBuf;//Reading of the width and height of the image.


        in.read(reinterpret_cast<char*>(&wBuf), sizeof(wBuf));//Reading of the number of planes. Must be 1.
        if(wBuf != 1)return in;//Error. Must be 1.

        in.read(reinterpret_cast<char*>(&wBuf), sizeof(wBuf));//Reading of the number of bits per pixel.
        if((wBuf != 1) & (wBuf != 2) & (wBuf != 4) & (wBuf != 8) & (wBuf != 24) & (wBuf !=32)) return in;
        //Error! This value must be 1, 4, 8, 24 or 32.
        inf.bitCount = wBuf;


        in.read(reinterpret_cast<char*>(&dBuf), sizeof(dBuf));//Reading of the type of the compression.
        inf.compr = dBuf;

        in.read(reinterpret_cast<char*>(&dBuf), sizeof(dBuf));//Reading of the image size.
        inf.imagSize = dBuf;


        in.read(reinterpret_cast<char*>(&lBuf), sizeof(lBuf));
        inf.xRes = lBuf;

        in.read(reinterpret_cast<char*>(&lBuf), sizeof(lBuf));
        inf.yRes = lBuf;
        //Reading of the resolution of the image horizontal and vertical resulution. This values are not uses.


        in.read(reinterpret_cast<char*>(&dBuf), sizeof(dBuf));//Reading of the number of using colors.
        inf.clrUsed = dBuf;

        in.read(reinterpret_cast<char*>(&dBuf), sizeof(dBuf));//Reading of the important indexes.
        inf.clrImp = dBuf;


        return in;
    }
};
