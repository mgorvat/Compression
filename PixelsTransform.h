#ifndef PIXELSTRANSFORM_H_INCLUDED
#define PIXELSTRANSFORM_H_INCLUDED

#include "YUVPixel.h"
#include "RGBPixel.h"
#include "YUVPixelSet.h"
#include "RGBPixelSet.h"

using namespace Compression;

RGBPixel* YUVToRGB(YUVPixel *px);
YUVPixel* RGBToYUV(RGBPixel *px);
YUVPixelSet* RGBSetToYUVSet(RGBPixelSet *rgbSet);
RGBPixelSet* YUVSetToRGBSet(YUVPixelSet *yuvSet);

#endif // PIXELSTRANSFORM_H_INCLUDED
