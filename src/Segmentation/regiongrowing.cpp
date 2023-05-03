#include "regiongrowing.h"

// Constructor
RegionGrowing::RegionGrowing(){

}

// Define the function to check if a pixel is within the image bounds
bool RegionGrowing::isPixelInBounds(const cv::Mat& image, int row, int col) {
    return row >= 0 && row < image.rows && col >= 0 && col < image.cols;
}

// Define the region growing function
cv::Mat RegionGrowing::growRegion(cv::Mat inputImage, int seedRow, int seedCol, int threshold, cv::Size m_imageSize) {

    // Define key variables
    Pixel currentPixel;
    int neighborRow, neighborCol;
    int diff;

    // Initialize output image
    cv::Mat outputImage = cv::Mat::zeros(m_imageSize, CV_8UC1);

    // Convert input image to LUV colorspace
    cv::Mat luvImage;
    cv::cvtColor(inputImage, luvImage, cv::COLOR_BGR2Luv);

    // Resize the input image to m_imageSize
    cv::resize(luvImage, luvImage, m_imageSize);

    // Create a queue to store the pixels to be processed
    std::queue<Pixel> pixelQueue;

    // Add the seed pixel to the queue and mark it as processed
    pixelQueue.push({seedRow, seedCol});
    outputImage.at<uchar>(seedRow, seedCol) = 255;

    // Define the neighborhood of a pixel
    int neighborhood[8][2] = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};

    // Process the pixels in the queue
    while (!pixelQueue.empty()) {
        // Get the next pixel from the queue
        currentPixel = pixelQueue.front();
        pixelQueue.pop();

        // Process the pixel's neighbors
        for (int i = 0; i < 8; i++) {
            neighborRow = currentPixel.row + neighborhood[i][0];
            neighborCol = currentPixel.col + neighborhood[i][1];

            // Check if the neighbor is within the image bounds
            if (isPixelInBounds(luvImage, neighborRow, neighborCol)) {
                // Check if the neighbor pixel is within the threshold value
                diff = cv::norm(luvImage.at<cv::Vec3b>(currentPixel.row, currentPixel.col), luvImage.at<cv::Vec3b>(neighborRow, neighborCol), cv::NORM_L2);
                if (diff <= threshold && outputImage.at<uchar>(neighborRow, neighborCol) == 0) {
                    // Add the neighbor pixel to the queue and mark it as processed
                    pixelQueue.push({neighborRow, neighborCol});
                    outputImage.at<uchar>(neighborRow, neighborCol) = 255;
                }
            }
        }
    }
    return outputImage;
}
