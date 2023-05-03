#include "kmeanssegmentation.h"

using namespace cv;
using namespace std;

KmeansSegmentation::KmeansSegmentation()
{

}

//void KmeansSegmentation::EuclideanDistance(Mat DataPoints, Mat labels, Mat& centroids)
//{
//  for (int k = 0; k < centroids.rows; k++)
//    {   cout<<1<<endl;
//      Mat clusterPoints = Mat::zeros(0, DataPoints.cols, DataPoints.type());
//      for (int row = 0; row < labels.rows; row++)
//        {
//          if (labels.at<int>(row, 0) == k)
//            {
//              clusterPoints.push_back(DataPoints.row(row));
//            }
//          cout<<2<<endl;
//        }
//      if (!clusterPoints.empty())
//        {
//          Mat mean = Mat::zeros(1, DataPoints.cols, DataPoints.type());
//          reduce(clusterPoints, mean, 0, REDUCE_AVG);
//          mean.copyTo(centroids.row(k));
//        }
//      cout<<3<<endl;
//    }
//}

Mat KmeansSegmentation::KmeansDrivingFunction(Mat SrcImg, int n_clusters)
{

  //      cvtColor(SrcImg, SrcImg, COLOR_BGR2RGB);
  //this part is to scale down the image for smaller size and faster excution of the algorithm
  //      int ScaleSize = 20;
  //      int NewWidth = (SrcImg.rows* 20/100);
  //      int NewHeight = (SrcImg.cols* 20/100);
  //      Mat NewImg = Mat(NewWidth, NewHeight, CV_8UC3);
  //      resize(SrcImg, NewImg, 0, 0, INER_AREA);
  //alternativly we convert the image to data points to feed to the kmeans algorithm directly
  //      Mat DataPoints;
  //      SrcImg.convertTo(DataPoints, CV_32F);
  //      DataPoints.reshape(3, SrcImg.cols* SrcImg.rows);
  //      Mat labels, centers;
  //      KmeansClustering(DataPoints, n_clusters, labels, centers);


  // Convert the input image to a matrix of data points
  Mat dataPoints = SrcImg.reshape(1, SrcImg.rows * SrcImg.cols);
  dataPoints.convertTo(dataPoints, CV_32F);

  // Initialize the labels and centroids matrices
  Mat labels(dataPoints.rows, 1,CV_32S);
  Mat centroids(n_clusters, dataPoints.cols, CV_32F);

  // Initialize the centroids randomly
  randu(centroids, Scalar::all(0), Scalar::all(255));

  // Perform K-means clustering
  KmeansClustering(dataPoints, n_clusters, labels, centroids);

  // Reshape the labels matrix to match the input image dimensions
  Mat segmented = labels.reshape(1, SrcImg.rows);

  // Convert the label values to colors for display
  Mat colors;
  convertScaleAbs(segmented, colors, 255.0 / (n_clusters - 1));

  return colors;

}
//Mat KmeansSegmentation::InitializeCentorids(Mat DataPoints, int n_clusters)
//{
//  Mat initialCentroids(n_clusters, DataPoints.cols, CV_32F);
//  int numRows = DataPoints.rows;
//  srand(time(NULL));
//  vector<int> randomIndices(n_clusters);
//  for(int k = 0; k < n_clusters; k++)
//  {
//      randomIndices[k] = rand() % numRows;
//  }
//  for(int k = 0; k < n_clusters; k++)
//  {
//      DataPoints.row(randomIndices[k]).copyTo(initialCentroids.row(k));
//  }
//    return initialCentroids;
//}
void KmeansSegmentation::UpdateCentroids(Mat DataPoints, Mat labels, Mat& centroids)
{
  for (int k = 0; k < centroids.rows; k++) {
      if (k < centroids.rows) {
          Mat clusterPoints;
          for (int row = 0; row < labels.rows; row++) {
              if (labels.at<int>(row, 0) == k) {
                  clusterPoints.push_back(DataPoints.row(row));
                }
            }
          if (!clusterPoints.empty()) {
              Mat mean = clusterPoints.clone();
              reduce(mean.begin<float>(), mean.end<float>(), 0, std::plus<>());
              mean.copyTo(centroids.row(k));
            }
        }
    }
}
void KmeansSegmentation::KmeansClustering(Mat DataPoints, int n_clusters, Mat labels, Mat centroids, int maxIterations)
{
  double minDistValue = -numeric_limits<double>::infinity();
  Mat prevCentroids(n_clusters, centroids.cols, CV_32F);
  int iterator = 0;
  //the loop excutes as long as number of max iterations is not exceeded and the centroids values change
  while(iterator < maxIterations && countNonZero(centroids != prevCentroids) > 0)
    {
      prevCentroids = centroids.clone();

      //for each pixel value in the DataPoints
      for (int i = 0; i < DataPoints.rows; i++)
        {
          double minDist = numeric_limits<double>::max();
          int label = 0;
          for (int k = 0; k < centroids.rows; k++) {
              double dist = norm(DataPoints.row(i) - centroids.row(k));
              if (dist < minDist) {
                  minDist = dist;
                  label = k;
                }
            }
          labels.at<int>(i, 0) = label;
        }
      UpdateCentroids(DataPoints, labels, centroids);
      cout<<3<<endl;
      iterator++;
    }
}
