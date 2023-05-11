#include "detectFaces.h"

std::vector<cv::Mat> croppedFaces(cv::Mat inputImage, cv::CascadeClassifier cascade) {
    // Convert input image to grayscale
    cv::Mat grayImage;
    cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

    // Detect faces using cascade classifier
    std::vector<cv::Rect> faces;
    cascade.detectMultiScale(grayImage, faces);

    // Crop image to include all detected faces
    std::vector<cv::Mat> croppedImages;
    for (const auto& face : faces) {
        cv::Mat croppedImage = inputImage(face);
        croppedImages.push_back(croppedImage);
    }

    return croppedImages;
}

int detectFaces(cv::CascadeClassifier cascade, cv::Mat inputImage, std::vector<cv::Mat>& matObjects) {
    cv::Mat resizedImage;

    // Resize input image to a fixed size
    cv::resize(inputImage, inputImage, cv::Size(700, 700));

    // Call detectFaces function to crop image to include all detected faces
    std::vector<cv::Mat> croppedImages = croppedFaces(inputImage, cascade);

    if (croppedImages.empty()) {
        // No faces detected
        return 0;
    }

    // Resize and store cropped images in the vector of matrices
    matObjects.resize(croppedImages.size());
    for (unsigned long i = 0; i < croppedImages.size(); i++) {
        cv::resize(croppedImages[i], resizedImage, cv::Size(200, 200));
        matObjects[i] = resizedImage.clone();  // Use clone to avoid overwriting the same image
    }

    return 1;
}

/***    Implementation example

#include "detectFaces.h"

int main() {
    // Load Haar Cascade classifier for face detection
    cv::CascadeClassifier cascade;
    cascade.load("D:\\C++ Projects\\cascade_classifier\\Resources\\cascadeFaceClassifier.xml");

    // Load input image
    cv::Mat inputImage = cv::imread("C:\\Users\\MAI\\Downloads\\dog face.jpg");

    std::vector<cv::Mat> matObjects;

    bool isPerson = detectFaces(cascade, inputImage, matObjects);

    if (isPerson){
    // Display cropped images with different window names
    for (unsigned long i = 0; i < matObjects.size(); i++) {
        cv::imshow("Cropped Image " + std::to_string(i + 1), matObjects[i]);
    }
    cv::waitKey(0);
    }

    return 0;
}

***/
