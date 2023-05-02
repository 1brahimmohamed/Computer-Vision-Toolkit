#ifndef AGGLOMERATIVE_H
#define AGGLOMERATIVE_H

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QDebug>

class Agglomerative
{
public:
  Agglomerative();
  static cv::Mat agglomarativeSegmentation(cv::Mat input, int num_clusters);

private:
  static float calculateDistance(cv::Vec3b a, cv::Vec3b b);
  static cv::Vec3b mergeClusters(cv::Vec3b a, cv::Vec3b y);
};

#endif // AGGLOMERATIVE_H
