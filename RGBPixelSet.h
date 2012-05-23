#ifndef RGBPIXELSET_H_INCLUDED
#define RGBPIXELSET_H_INCLUDED

#include <vector>
#include <algorithm>
#include "RGBPixel.h"

namespace Compression {
    class RGBPixelSet {
        public:
            RGBPixelSet(int width, int height):width(width), height(height){
                image.reserve(width*height);
            }

            void addPixel(RGBPixel px){
                image.push_back(px);
            }
            RGBPixel* getPixel(int ind){ return &(image[ind]); }
            RGBPixel* getPixel(int x, int y){ return &(image[x * width + y]); }
            int getHeight(){return height;}
            int getWidth(){return width;}
            int getSize(){return height * width;}

        private:
            std::vector<RGBPixel> image;
            int width, height;
    };
}
#endif
