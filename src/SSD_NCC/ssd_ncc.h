#ifndef SSD_NCC_H
#define SSD_NCC_H
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;

class SSD_NCC
{
public:
    SSD_NCC();
    static double ssd (vector<double> v1, vector<double> v2);
    static double ncc(vector<double> v1, vector<double> v2);
    static vector<int> matchFeatures(vector<vector<double>> features1, vector<vector<double>> features2, bool useNCC);
    static cv::Mat matchImagesDriver(cv::Mat Image1, cv::Mat Image2);
};



#endif // SSD_NCC_H
