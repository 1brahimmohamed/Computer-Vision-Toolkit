#include "detectfaces.h"

DetectFaces::DetectFaces()
{

}

vector<Mat> DetectFaces::croppedFaces(Mat inputImage, CascadeClassifier cascade) {
  // Convert input image to grayscale
  Mat grayImage;
  cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

  // Detect faces using cascade classifier
  vector<Rect> faces;
  cascade.detectMultiScale(grayImage, faces);

  // Crop image to include all detected faces
  std::vector<Mat> croppedImages;
  for (const auto& face : faces) {
      Mat croppedImage = inputImage(face);
      croppedImages.push_back(croppedImage);
    }

  return croppedImages;
}

int DetectFaces::detectFaces(CascadeClassifier cascade, Mat inputImage, vector<Mat>& matObjects) {
  Mat resizedImage;

  // Resize input image to a fixed size
  resize(inputImage, inputImage, cv::Size(700, 700));

  // Call detectFaces function to crop image to include all detected faces
  vector<Mat> croppedImages = croppedFaces(inputImage, cascade);

  if (croppedImages.empty()) {
      // No faces detected
      return 0;
    }

  // Resize and store cropped images in the vector of matrices
  matObjects.resize(croppedImages.size());
  for (unsigned long i = 0; i < croppedImages.size(); i++) {
      resize(croppedImages[i], resizedImage, Size(200, 200));
      matObjects[i] = resizedImage.clone();  // Use clone to avoid overwriting the same image
    }

  return 1;
}
