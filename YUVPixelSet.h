#ifndef YUVPIXELSET_H_INCLUDED
#define YUVPIXELSET_H_INCLUDED

#include <vector>
#include "YUVPixel.h"

using namespace std;

//TODO: Make destructor
namespace Compression{
    class YUVPixelSet{
        public:
            YUVPixelSet(int width, int height):width(width), height(height){
                image.reserve(width*height);
            }

            void addPixel(YUVPixel px){
                image.push_back(px);
            }
            YUVPixel* getPixel(int ind){return &(image[ind]);}
            YUVPixel* getPixel(int x, int y){return &(image[x * width + y]);}
            int getHeight(){return height;}
            int getWidth(){return width;}
            int getSize(){return height * width;}
        private:
            vector<YUVPixel> image;
            int width, height;
    };
}
#endif
