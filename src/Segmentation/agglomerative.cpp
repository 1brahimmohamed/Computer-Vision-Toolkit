#include "agglomerative.h"

Agglomerative::Agglomerative()
{

}

//Distance for 3 channels images
float Agglomerative::calculateDistance(cv::Vec3b a, cv::Vec3b b) {
  return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2) + pow(a[2] - b[2], 2));
}

// Define merge function for merging two clusters
cv::Vec3b Agglomerative::mergeClusters(cv::Vec3b a, cv::Vec3b y) {
  int r = (a[0] + y[0]) / 2;
  int g = (a[1] + y[1]) / 2;
  int b = (a[2] + y[2]) / 2;
  return cv::Vec3b(static_cast<uchar>(r), static_cast<uchar>(g), static_cast<uchar>(b));

}

cv::Mat Agglomerative::agglomarativeSegmentation(cv::Mat input, int numberOfClusters) {


  cv::cvtColor(input, input, cv::COLOR_BGR2Luv);

  cv::Mat segmentedImage;
  segmentedImage.create(input.size(), input.type());

  // Initialize the clusters
  std::vector<cv::Vec3b> clusters;

  for (int i = 0; i < input.rows; i++) {
      for (int j = 0; j < input.cols; j++) {
          clusters.push_back(input.at<cv::Vec3b>(i, j));
        }
    }

  // Perform agglomerative clustering baseed on stopping criteria
  while (clusters.size() > numberOfClusters) {
      qDebug() << "n_c " << clusters.size();
      // Find the two closest clusters
      float min_dist = FLT_MAX;
      int min_i, min_j;
      for (int i = 0; i < clusters.size(); i++) {
          for (int j = i + 1; j < clusters.size(); j++) {
              float dist = calculateDistance(clusters[i], clusters[j]);
              if (dist < min_dist) {
                  min_dist = dist;
                  min_i = i;
                  min_j = j;
                }
            }
        }

      // Merge the two clusters
      clusters[min_i] = mergeClusters(clusters[min_i], clusters[min_j]);
      clusters.erase(clusters.begin() + min_j);
    }

  // Assign labels to the pixels
  cv::Mat labels(input.size(), CV_32S);
  for (int i = 0; i < input.rows; i++) {
      for (int j = 0; j < input.cols; j++) {
          int min_cluster = 0;
          float min_dist = FLT_MAX;
          for (int k = 0; k < clusters.size(); k++) {
              float dist = calculateDistance(input.at<cv::Vec3b>(i, j), clusters[k]);
              if (dist < min_dist) {
                  min_dist = dist;
                  min_cluster = k;
                }
            }
          labels.at<int>(i, j) = min_cluster;
        }
    }

  // Visualize the segmentation
  for (int i = 0; i < input.rows; i++) {
      for (int j = 0; j < input.cols; j++) {
          cv::Vec3b color = clusters[labels.at<int>(i, j)];
          segmentedImage.at<cv::Vec3b>(i, j) = color;
        }
    }

  cv::cvtColor(segmentedImage, segmentedImage, cv::COLOR_Luv2BGR);
  return segmentedImage;
}
