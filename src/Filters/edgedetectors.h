#ifndef EDGEDETECTORS_H
#define EDGEDETECTORS_H
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include<cstdint>
#include <iostream>
using namespace cv;
using namespace std;
class EdgeDetectors
{
public:
    EdgeDetectors();
   ~EdgeDetectors();
    Mat CannyEdgeDetector(Mat srcImg);
    Mat RobertEdgeDetector(Mat SrcImg);
    Mat PerwittEdgeDetector(Mat SrcImg);
    Mat SobalEdgeDetector(Mat SrcImg);
};

#endif // EDGEDETECTORS_H
