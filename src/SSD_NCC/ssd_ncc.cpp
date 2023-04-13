#include "ssd_ncc.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <QElapsedTimer>
#include <QDebug>

using namespace std;
using namespace cv;

SSD_NCC::SSD_NCC()
{

}

// Compute sum of squared differences between two vectors
double SSD_NCC::ssd(vector<double> v1, vector<double> v2)
{
  double sum = 0.0;
  for (int i = 0; i < v1.size(); i++)
    {
      sum += pow(v1[i] - v2[i], 2);
    }
  return sum;
}

// Compute normalized cross-correlation between two vectors
double SSD_NCC::ncc(vector<double> v1, vector<double> v2)
{
  double mean1 = 0.0, mean2 = 0.0, std1 = 0.0, std2 = 0.0, cov = 0.0;
  int n = v1.size();
  for (int i = 0; i < n; i++)
    {
      mean1 += v1[i];
      mean2 += v2[i];
    }
  mean1 /= n;
  mean2 /= n;
  for (int i = 0; i < n; i++)
    {
      std1 += pow(v1[i] - mean1, 2);
      std2 += pow(v2[i] - mean2, 2);
      cov += (v1[i] - mean1) * (v2[i] - mean2);
    }
  std1 = sqrt(std1 / n);
  std2 = sqrt(std2 / n);
  cov /= n;
  return (cov / (std1 * std2));
}


// Match two sets of features using SSD or NCC
vector<int> SSD_NCC::matchFeatures(vector<vector<double>> features1, vector<vector<double>> features2, bool useNCC)
{
  // Compute distances between all pairs of feature vectors using SSD and NCC
  vector<vector<double>> distances(features1.size(), vector<double>(features2.size()));
  for (int i = 0; i < features1.size(); i++)
    {
      for (int j = 0; j < features2.size(); j++)
        {
          if (useNCC)
            {
              distances[i][j] = ncc(features1[i], features2[j]); // NCC distance
            }
          else
            {
              distances[i][j] = ssd(features1[i], features2[j]); // SSD distance
            }
        }
    }

  // Find the best match for each feature vector
  vector<int> matches(features1.size());
  for (int i = 0; i < features1.size(); i++)
    {
      double min_distance = distances[i][0];
      int min_index = 0;
      for (int j = 1; j < features2.size(); j++)
        {
          if (distances[i][j] < min_distance)
            {
              min_distance = distances[i][j];
              min_index = j;
            }
        }
      matches[i] = min_index;
    }

  return matches;
}


vector<Mat> match_images(const vector<Mat>& image_set)
{
  vector<Mat> sorted_images;
  vector<double> ssd_values;
  vector<double> ncc_values;

  // Convert images to grayscale
  vector<Mat> gray_images;
  for (const auto& img : image_set) {
      Mat gray_img;
      cvtColor(img, gray_img, COLOR_BGR2GRAY);
      gray_images.push_back(gray_img);
    }

  // Choose reference image
  const Mat& reference_img = gray_images[0];

  // Calculate features for reference image
  Ptr<Feature2D> sift = SIFT::create();
  vector<KeyPoint> kp1;
  Mat des1;
  sift->detectAndCompute(reference_img, noArray(), kp1, des1);

  // Calculate SSD and NCC for each image
  for (size_t i = 1; i < gray_images.size(); i++) {
      // Calculate features for current image
      vector<KeyPoint> kp2;
      Mat des2;
      sift->detectAndCompute(gray_images[i], noArray(), kp2, des2);

      // Calculate SSD
      double ssd = norm(des1 - des2, NORM_L2);
      ssd_values.push_back(ssd);

      // Calculate NCC
      Mat result;
      matchTemplate(des1, des2, result, TM_CCOEFF_NORMED);
      double ncc = result.at<float>(0, 0);
      ncc_values.push_back(ncc);
    }

  // Sort images based on SSD and NCC values
  vector<size_t> ssd_indices(ssd_values.size());
  // iota(ssd_indices.begin(), ssd_indices.end(), 0);
  sort(ssd_indices.begin(), ssd_indices.end(),
       [&ssd_values](size_t i, size_t j) { return ssd_values[i] < ssd_values[j]; });

  vector<size_t> ncc_indices(ncc_values.size());
  // iota(ncc_indices.begin(), ncc_indices.end(), 0);
  sort(ncc_indices.begin(), ncc_indices.end(),
       [&ncc_values](size_t i, size_t j) { return ncc_values[i] > ncc_values[j]; });

  // Arrange images in sorted order
  for (const auto& i : ncc_indices) {
      sorted_images.push_back(image_set[i + 1]);
    }

  return sorted_images;
}


Mat SSD_NCC::matchImagesDriver(Mat Image1, Mat Image2){
  Mat gray1, gray2;
  cvtColor(Image1, gray1, COLOR_BGR2GRAY);
  cvtColor(Image2, gray2, COLOR_BGR2GRAY);

  // Detect SIFT features
  Ptr<Feature2D> sift = SIFT::create();
  vector<KeyPoint> keypoints1, keypoints2;
  sift->detect(gray1, keypoints1);
  sift->detect(gray2, keypoints2);

  // Extract SIFT descriptors
  Mat descriptors1, descriptors2;
  sift->compute(gray1, keypoints1, descriptors1);
  sift->compute(gray2, keypoints2, descriptors2);


  // Convert descriptors to vector<vector<double>>
  vector<vector<double>> features1(descriptors1.rows, vector<double>(descriptors1.cols));
  vector<vector<double>> features2(descriptors2.rows, vector<double>(descriptors2.cols));

  for (int i = 0; i < descriptors1.rows; i++) {
      for (int j = 0; j < descriptors1.cols; j++) {
          features1[i][j] = descriptors1.at<float>(i, j);
        }
    }
  for (int i = 0; i < descriptors2.rows; i++) {
      for (int j = 0; j < descriptors2.cols; j++) {
          features2[i][j] = descriptors2.at<float>(i, j);
        }
    }

  for (int i = 0; i < features1.size(); i++)
    {
      keypoints1.push_back(KeyPoint(Point2f(features1[i][0], features1[i][1]), 1.0));
    }
  for (int i = 0; i < features2.size(); i++)
    {
      keypoints2.push_back(KeyPoint(Point2f(features2[i][0], features2[i][1]), 1.0));
    }

  // Call matchFeatures with SSD
  QElapsedTimer timerSSD;
  timerSSD.start();

  vector<int> matches_ssd = matchFeatures(features1, features2, true);

  qint64 elapsedSSD = timerSSD.elapsed();
  qDebug() << "SSD Elapsed time:" << elapsedSSD << "ms";

  vector<DMatch> matches1to2_ssd;
  for (int i = 0; i < matches_ssd.size(); i++)
    {
      matches1to2_ssd.push_back(DMatch(i, matches_ssd[i], 0));
    }


  // Call matchFeatures with NCC
  QElapsedTimer timerNCC;
  timerNCC.start();

  vector<int> matches_ncc = matchFeatures(features1, features2, false);

  qint64 elapsedNCC = timerNCC.elapsed();
  qDebug() << "NCC Elapsed time:" << elapsedNCC << "ms";

  vector<DMatch> matches1to2_ncc;
  for (int i = 0; i < matches_ncc.size(); i++)
    {
      matches1to2_ncc.push_back(DMatch(i, matches_ncc[i], 0));
    }

  // Draw matches on images
  Mat img_matches;
  drawMatches(Image1, keypoints1, Image2, keypoints2, matches1to2_ssd, img_matches);

  return img_matches;
}
