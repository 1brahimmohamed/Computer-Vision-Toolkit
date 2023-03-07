#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;


class Histogram
{
public:
    Histogram();
    ~Histogram();
    void Histo(Mat image, int histogram[]);
    void cumhist(int histogram[], int cumhistogram[]);
    void histDisplay(int histogram[], const char* name);
    int calc_image_size(Mat image);
    Mat equilization(Mat image, int histogram[], int cumhistogram[],int Sk[]);
    void equalized_Histogram(Mat image, int final[],int histogram[],int Sk[]);

//private:
    int histogram[256];
    int cumhistogram[256];
    int final[256];
    int Sk[256];

};

#endif // HISTOGRAM_H
