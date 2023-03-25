#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>
#include "cvector.h"
#include <string.h>


namespace img
{
    typedef enum {
        THRESH_BIN,
        THRESH_BIN_INV
    }t_types;
    typedef enum {
        ADAPTIVE_THRESH_MEAN,
        ADAPTIVE_THRESH_GAUSSIAN
    }a_types;
    typedef enum {
        LOW_PASS_FILTER,
        HIGH_PASS_FILTER
    }p_types;
    class Image
    {
    public:
        cv::Mat mat;
        cvector<uchar> pixels;
        Image(){};
        Image(std::string path);
        Image(cv::Mat mat);
        Image(cvector<uchar> pixels, size_t rows, size_t cols, int type);
        void display(std::string title) const;
        void vectorize();
    };
    cvector<double> filter(const Image &img, cvector<cvector<double>> mask);
    Image merge(const cvector<Image> &imgs);
    Image convert(const Image &img, std::string from, std::string to);
    cvector<Image> split(const Image &img);
    cvector<double> sobel(const Image &img, bool dx = true, bool dy = true);
    cvector<uchar> scale(cvector<double> pixels);
    Image noise_filter(Image &source, int size, std::string type, double std = 1);
};

#endif
