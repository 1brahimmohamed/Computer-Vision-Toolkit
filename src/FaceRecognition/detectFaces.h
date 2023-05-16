#ifndef DETECTFACES_H
#define DETECTFACES_H

#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <QDir>

using namespace std;
using namespace cv;

class DetectFaces
{
public:
  DetectFaces();

  // Function to detect faces in the input image and store the cropped images
  static int detectFaces(CascadeClassifier cascade, Mat inputImage, std::vector<cv::Mat>& matObjects);

private:

  QDir currentDir;
  QString classiferFilePath;
  CascadeClassifier cascade;

  // Function to crop faces from the input image
  static vector<Mat> croppedFaces(Mat inputImage, CascadeClassifier cascade);

};

#endif // DETECTFACES_H
