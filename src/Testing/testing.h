#ifndef TESTING_H
#define TESTING_H

#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class testing
{
public:
    testing();
    static double euclideanDistance(const std::vector<double>& vector1, const std::vector<double>& vector2);
    static vector<double> test_image_preprocessing (const std::vector<int>& test_image);
    static tuple<string,bool> predict( const cv::Mat& train_weights, const std::vector<string>& train_labels,const std::vector<int>& test_image, double threshold = 2e8);
    static tuple<int, int, int, int> computeMetrics( const cv::Mat& train_weights, const std::vector<string>& train_labels, const cv::Mat& test_matrix, const std::vector<string>& test_labels, double threshold = 2e8) ;

};

#endif // TESTING_H
