#include "PixelsTransform.h"

// TODO: Comment this
RGBPixel* YUVToRGB(YUVPixel *px){
    RGBPixel* res = new RGBPixel();
    res->red = px->Y + 1.402 * px->Cr - 179.456;
    res->green = px->Y - 0.34414 * px->Cb - 0.71414 * px->Cr + 135.45984;
    res->blue = px->Y + 1.772 * px->Cb - 226.816;
    return res;
}

YUVPixel* RGBToYUV(RGBPixel *px){
    YUVPixel* res = new YUVPixel();
    res->Y = (77.0 / 256) * px->red + (150.0 / 256) * px->green + (29.0 / 256) * px->blue;
    res->Cr = (131.0 / 256) * px->red - (110.0 / 256) * px->green - (21.0 / 256) * px->blue + 128;
    res->Cb = -(44.0 / 256) * px->red - (87.0 / 256) * px->green + (131.0 / 256) * px->blue + 128;
    return res;
}

YUVPixelSet* RGBSetToYUVSet(RGBPixelSet *rgbSet){
    YUVPixelSet *res = new YUVPixelSet(rgbSet->getWidth(), rgbSet->getHeight());
    for(int i = 0; i < rgbSet->getSize(); i++)
        res->addPixel(*RGBToYUV(rgbSet->getPixel(i)));
    return res;
}

RGBPixelSet* YUVSetToRGBSet(YUVPixelSet *yuvSet){
    RGBPixelSet *res = new RGBPixelSet(yuvSet->getWidth(), yuvSet->getHeight());
    for(int i = 0; i < yuvSet->getSize(); i++)
        res->addPixel(*YUVToRGB(yuvSet->getPixel(i)));
    return res;
}
