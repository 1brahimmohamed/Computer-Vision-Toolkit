#ifndef KMEANSSEGMENTATION_H
#define KMEANSSEGMENTATION_H
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/core.hpp>
#include<cmath>
#include<cstdint>
#include <random>
#include <iostream>
#include <vector>
#include<string>
using namespace cv;
using namespace std;

class KmeansSegmentation
{
public:
    KmeansSegmentation();
    static void EuclideanDistance(Mat DataPoints, Mat labels, Mat& centroids);
    static Mat InitializeCentorids(Mat DataPoints, int n_clusters=2);
    static void UpdateCentroids(Mat DataPoints, Mat labels, Mat& centroids);
    static void KmeansClustering(Mat DataPoints, int n_clusters, Mat labels, Mat centroids, int maxIterations = 200);
    static Mat KmeansDrivingFunction(Mat SrcImg, int n_clusters = 2);
};

#endif // KMEANSSEGMENTATION_H
