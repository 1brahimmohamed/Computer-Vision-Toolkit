#include "src/UI/mainwindow.h"
#include <QApplication>


#include <opencv2/opencv.hpp>
#include "src/Filters/threshold.h"
#include "src/ActiveContour/active_contour.h"




int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

/* Code to run active_contours
 * Parameters Needed:
 * Alpha (0.1-10) float 0.1
 * Beta (0.1-10) float 0.1
 * Gamma (1-50) int 1
 * Radius (1-500) int 1
 * Points (50-300) int 10
 * Iterations (1-100) int 1
*/

//cv::Mat src_act = cv::imread("C:\\Users\\mahmo\\OneDrive\\Desktop\\img3.jpg", cv::IMREAD_GRAYSCALE);
//cv::Mat dst_act = ACTIVE_CONTOUR::active_contour(src_act, 20, 2.5, 0.9, 20, 80, 100);
//cv::imshow("Hello World", dst_act);
//cv::waitKey();


/* Code to run threshold
*
* Global threshold Parameters:
* global_threshold (0-255) int 1
*
* Local threshold Parameters:
* block_size (1-3-5-7-9-11-13-15-17-19-21-23-25-27-28-30)
* k_value (0.01-1) float 0.01
*/

cv::Mat inputImage = cv::imread("C:\\Users\\mahmo\\OneDrive\\Desktop\\img3.jpg", cv::IMREAD_GRAYSCALE);

// Apply global thresholding with a threshold value of 128
cv::Mat globalThresholdedImage = THRESHOLD_H::GlobalthresholdImage(inputImage, 128);

// Apply local thresholding with a block size of 11 and a k value of 0.2
cv::Mat localThresholdedImage = THRESHOLD_H::LocalThresholdImage(inputImage, 11, 0.2);

// Display the original and thresholded images
cv::imshow("Input Image", inputImage);
cv::imshow("Global Thresholded Image", globalThresholdedImage);
cv::imshow("Local Thresholded Image", localThresholdedImage);
cv::waitKey(0);


  return a.exec();
}
