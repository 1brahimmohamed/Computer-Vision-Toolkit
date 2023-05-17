#include "testing.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>

using namespace std;
using namespace cv;

double euclideanDistance(const std::vector<double>& vector1, const std::vector<double>& vector2) {
    if (vector1.size() != vector2.size()) {
        std::cerr << "Vectors must have the same size!" << std::endl;
        return -1.0;
    }

    double distance = 0.0;
    for (size_t i = 0; i < vector1.size(); ++i) {
        distance += std::pow(vector1[i] - vector2[i], 2);
    }

    return std::sqrt(distance);
}

vector<double> test_image_preprocessing (const std::vector<int>& test_image){

    //Test image normalization
    vector<int> normalized_test_image;
//    normalized_test_image=Normalization();



   //Computing Test image weights
    vector<double> test_weights;
//   test_weights=calculateImageWeights();

   return test_weights;
}

tuple<string,bool> predict( const cv::Mat& train_weights, const std::vector<string>& train_labels,const std::vector<int>& test_image, double threshold = 2e8) {

    //calculating test image weights
    vector<double> test_weights;
    test_weights=test_image_preprocessing(test_image);


    //Calculating euclidean distances between the test image and each training image
    vector<double> euclidean_dist;
    for (int j=0; j<train_weights.cols; j++) {
            euclidean_dist[j]=euclideanDistance(train_weights.row(j),test_weights);
        }

    // Index of image with least Euclidean_dist
    int index = -1;
    //minimum distance between the test image and the one of the training images
    double min_dist =10000000.0;

    for (int k = 0; k < train_weights.cols; ++k) {
        double dist = euclidean_dist[k];
        if (dist < min_dist) {
            min_dist = dist;
            index = k;
        }
    }

    bool underThreshold=false;
    if (min_dist < threshold) underThreshold=true;

    string matched_image_label = train_labels[index];

    return make_tuple(matched_image_label, underThreshold);
}

tuple<int, int, int, int> computeMetrics( const cv::Mat& train_weights, const std::vector<string>& train_labels, const cv::Mat& test_matrix, const std::vector<string>& test_labels, double threshold = 2e8) {

    string matched_image_label;
    bool match= false;
    int true_positive = 0;
    int false_positive = 0;
    int true_negative = 0;
    int false_negative = 0;


    for(int i=0; i<test_matrix.rows; i++){

        auto [matched_image_label, underThreshold] = predict(train_weights,train_labels,test_matrix.row(i));

        //comparing the predicted label with the true label
        if(matched_image_label == test_labels[i])
            match=true;

        if (underThreshold) { // It's a face

           if (match) true_positive++;
           else false_positive++;
        }
        else {

           if (match) false_negative++;
           else true_negative++;

        }

    }


   return std::make_tuple(true_positive, false_positive, true_negative, false_negative);
 }
