#include "threshold.h"

using namespace cv;
using namespace std;


Mat GlobalthresholdImage(Mat inputImage, int thresholdValue)
{
    cvtColor(inputImage, inputImage, COLOR_BGR2GRAY);

    // Create a new output image with the same size as the input image
    Mat outputImage(inputImage.rows, inputImage.cols, CV_8UC1, Scalar(0));

    // Apply the threshold to each pixel of the input image
    for (int i = 0; i < inputImage.rows; i++)
    {
        for (int j = 0; j < inputImage.cols; j++)
        {
            int pixelValue = inputImage.at<uchar>(i, j);
            if (pixelValue >= thresholdValue)
            {
                outputImage.at<uchar>(i, j) = 255;
            }
        }
    }

    // return the thresholded image
    return outputImage;
}

Mat LocalThresholdImage(Mat inputImage, int blockSize, double k)
{
    cvtColor(inputImage, inputImage, COLOR_BGR2GRAY);

    // Create a new output image with the same size as the input image
    Mat outputImage(inputImage.rows, inputImage.cols, CV_8UC1, Scalar(0));

    // Pad the input image to handle edge cases
    Mat paddedImage;
    copyMakeBorder(inputImage, paddedImage, blockSize / 2, blockSize / 2, blockSize / 2, blockSize / 2, BORDER_REPLICATE);

    // Apply the threshold to each pixel of the input image
    for (int i = 0; i < inputImage.rows; i++)
    {
        for (int j = 0; j < inputImage.cols; j++)
        {
            // Compute the mean and standard deviation of the current block
            Mat block = paddedImage(Rect(j, i, blockSize, blockSize));
            Scalar mean, stddev;
            meanStdDev(block, mean, stddev);

            // Compute the threshold value using the local mean and standard deviation
            int thresholdValue = mean[0] * (1.0 - k * (stddev[0] / 128.0 - 1.0));

            // Apply the threshold to the current pixel
            int pixelValue = inputImage.at<uchar>(i, j);
            if (pixelValue >= thresholdValue)
            {
                outputImage.at<uchar>(i, j) = 255;
            }
        }
    }

    // return the thresholded image
    return outputImage;
}
