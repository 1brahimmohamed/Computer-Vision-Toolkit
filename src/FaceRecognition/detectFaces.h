#ifndef DETECTFACES_H
#define DETECTFACES_H

#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

// Function to crop faces from the input image
std::vector<cv::Mat> croppedFaces(cv::Mat inputImage, cv::CascadeClassifier cascade);

// Function to detect faces in the input image and store the cropped images
int detectFaces(cv::CascadeClassifier cascade, cv::Mat inputImage, std::vector<cv::Mat>& matObjects);


#endif // DETECTFACES_H

//DON'T FORGET TO ADD THIS LIBRARY "-lopencv_objdetect470 \" IN .PRO FILE
