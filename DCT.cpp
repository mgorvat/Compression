#include <cmath>
#include <iostream>

#define PI 3.14159265
//TODO: comment this
using namespace std;

/*
    Previously computed matrixes for computing DCT fo 8*8 matrixes.
    Matix C and transpose C. DCT8(A) can be computed as C*A*CT.
*/
float C[]{0.353553, 0.353553, 0.353553, 0.353553, 0.353553, 0.353553, 0.353553, 0.353553,
           0.490393, 0.415735, 0.277785, 0.0975452, -0.0975452, -0.277785, -0.415735, -0.490393,
           0.46194, 0.191342, -0.191342, -0.46194, -0.46194, -0.191342, 0.191342, 0.46194,
           0.415735, -0.0975452, -0.490393, -0.277785, 0.277785, 0.490393, 0.0975452, -0.415735,
           0.353553, -0.353553, -0.353553, 0.353553, 0.353553, -0.353553, -0.353553, 0.353553,
           0.277785, -0.490393, 0.0975452, 0.415735, -0.415735, -0.0975452, 0.490393, -0.277785,
           0.191342, -0.46194, 0.46194, -0.191342, -0.191342, 0.46194, -0.46194, 0.191342,
           0.0975452, -0.277785, 0.415735, -0.490393, 0.490393, -0.415735, 0.277785, -0.0975451};

float CT[]{0.353553, 0.490393, 0.46194, 0.415735, 0.353553, 0.277785, 0.191342, 0.0975452,
            0.353553, 0.415735, 0.191342, -0.0975452, -0.353553, -0.490393, -0.46194, -0.277785,
            0.353553, 0.277785, -0.191342, -0.490393, -0.353553, 0.0975452, 0.46194, 0.415735,
            0.353553, 0.0975452, -0.46194, -0.277785, 0.353553, 0.415735, -0.191342, -0.490393,
            0.353553, -0.0975452, -0.46194, 0.277785, 0.353553, -0.415735, -0.191342, 0.490393,
            0.353553, -0.277785, -0.191342, 0.490393, -0.353553, -0.0975452, 0.46194, -0.415735,
            0.353553, -0.415735, 0.191342, 0.0975452, -0.353553, 0.490393, -0.46194, 0.277785,
            0.353553, -0.490393, 0.46194, -0.415735, 0.353553, -0.277785, 0.191342, -0.0975451};

/***
    Computing discrete cosine transform(DCT). Computes matrix 8*8.
    input:
        matrix � pointer to matrix. Matrix presenting as one dimensional array
    output:
        result of DCT. Matrix, represented as array
*/

float* DCT(float* matrix){
    float *res = new float[64];
    float *buf = new float[64];
    float sum;
    //Multiplicating C * matrix
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            sum = 0;
            for(int k = 0; k < 8; k++){
                sum+= C[i * 8 + k] * matrix[k * 8 + j];
            }
            buf[i * 8 + j] = sum;
        }
    }
    //Multiplicating (C * matrix) * CT
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            sum = 0;
            for(int k = 0; k < 8; k++){
                sum+= buf[i * 8 + k] * CT[k * 8 + j];
            }
            res[i * 8 + j] = sum;
        }
    }
    delete[] buf;
    return res;
}