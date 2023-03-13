#ifndef EDGEDETECTORS_H
#define EDGEDETECTORS_H

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

class EdgeDetectors
{
public:
    EdgeDetectors();
   ~EdgeDetectors();
    static Mat CannyEdgeDetector(Mat srcImg);
    static Mat RobertEdgeDetector(Mat SrcImg);
    static Mat PerwittEdgeDetector(Mat SrcImg);
    static Mat SobalEdgeDetector(Mat SrcImg);
};

#endif // EDGEDETECTORS_H
