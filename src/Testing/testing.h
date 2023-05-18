#ifndef TESTING_H
#define TESTING_H

#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <QString>
using namespace std;
using namespace cv;

class Testing
{
public:
    Testing();
    static double euclideanDistance(const std::vector<double>& vector1, const std::vector<double>& vector2);
    static Mat testImagePreprocessing (Mat testImage, Mat meanVector, Mat eigenFaces);
    static tuple<QString,bool> predict(Mat train_weights, vector<QString> train_labels,Mat test_image, Mat meanVector, Mat eigenFaces, double threshold);
    static tuple<int, int, int, int> computeMetrics( Mat train_weights,
                                                     vector<QString> train_labels,
                                                     Mat test_matrix,
                                                     vector<QString> test_labels,
                                                     Mat meanVector,
                                                     Mat eigenFaces);

};

#endif // TESTING_H
