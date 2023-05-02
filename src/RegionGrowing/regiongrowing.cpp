#include "regiongrowing.h"

// Constructor
RegionGrowing::RegionGrowing(cv::Size imageSize) : m_imageSize(imageSize) {}

// Define the function to check if a pixel is within the image bounds
bool RegionGrowing::isPixelInBounds(const cv::Mat& image, int row, int col) {
    return row >= 0 && row < image.rows && col >= 0 && col < image.cols;
}

// Define the region growing function
cv::Mat RegionGrowing::growRegion(cv::Mat& inputImage, int seedRow, int seedCol, int threshold) {

    // Define key variables
    Pixel currentPixel;
    int neighborRow, neighborCol;
    int diff;

    // Initialize output image
    cv::Mat outputImage = cv::Mat::zeros(m_imageSize, CV_8UC1);

    // Resize the input image to m_imageSize
    cv::resize(inputImage, inputImage, m_imageSize);

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
            if (isPixelInBounds(inputImage, neighborRow, neighborCol)) {
                // Check if the neighbor pixel is within the threshold value
                diff = abs(inputImage.at<uchar>(currentPixel.row, currentPixel.col) - inputImage.at<uchar>(neighborRow, neighborCol));
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



/* main.cpp implementation
 *
 *
#include "regiongrowing.h"

int main() {
    // Load the input image
    cv::Mat inputImage = imread("C:\\Users\\mahmo\\OneDrive\\Pictures\\Screenshots\\Screenshot 2023-03-22 013002.png", cv::IMREAD_GRAYSCALE);

    // Control Points in QT GUI
    int seedX = 400;  // Bounds are 0-800
    int seedY = 400; // Bounds are 0-800
    int threshold = 10; // Bounds are 0-255
    cv::Size ImageSize = cv::Size(800,800); // Set the numbers in your program

    // Create an instance of the RegionGrowing class
    RegionGrowing rg(ImageSize);

    // Call the growRegion function to perform region growing
    cv::Mat outputImage = rg.growRegion(inputImage, seedX, seedY, threshold);

    // Show the input and output images
    cv::namedWindow("Input Image", cv::WINDOW_NORMAL);
    cv::imshow("Input Image", inputImage);

    cv::namedWindow("Output Image", cv::WINDOW_NORMAL);
    cv::imshow("Output Image", outputImage);

    cv::waitKey(0);

    return 0;
}
*
*
*/
