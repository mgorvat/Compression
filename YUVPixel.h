#ifndef YUVPIXEL_H_INCLUDED
#define YUVPIXEL_H_INCLUDED

namespace Compression{
    struct YUVPixel{
        float Y;
        float Cr;
        float Cb;

        YUVPixel(){}
        YUVPixel(unsigned char Y, unsigned char Cr, unsigned char Cb):Y(Y), Cr(Cr), Cb(Cb){}
    };
}
#endif // YUVPIXEL_H_INCLUDED
