#include "testing.h"
#include "src/FaceRecognition/pca.h"
#include "src/FaceRecognition/imagepreproccessing.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <QDebug>
#include <limits.h>


using namespace std;
using namespace cv;


Testing::Testing(){}

double Testing::euclideanDistance(const std::vector<double>& vector1, const std::vector<double>& vector2) {
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

Mat Testing::testImagePreprocessing(Mat testImage, Mat meanVector, Mat eigenFaces){

   //Computing Test image weights
   Mat test_weights;

   test_weights=Pca::computeWeights(eigenFaces, testImage);

   return test_weights;
}

tuple<QString,bool> Testing::predict(Mat train_weights, vector<QString> train_labels,Mat test_image, Mat meanVector, Mat eigenFaces, double threshold=2e8){

    //calculating test image weights
    Mat test_weights;
    test_weights = testImagePreprocessing(test_image, meanVector, eigenFaces);

    //Calculating euclidean distances between the test image and each training image
    vector<double> euclidean_dist(train_weights.rows,0);

    for (int j=0; j<train_weights.rows; j++) {
            euclidean_dist[j]=euclideanDistance(train_weights.row(j),test_weights);
        }

    // Index of image with least Euclidean_dist
    int index = -1;
    //minimum distance between the test image and the one of the training images
    double min_dist = std::numeric_limits<float>::infinity();

    for (int k = 0; k < train_weights.cols; ++k) {
        double dist = euclidean_dist[k];
        if (dist < min_dist) {
            min_dist = dist;
            index = k;
        }
    }

    bool underThreshold=false;
    if (min_dist < threshold) underThreshold=true;

    QString matched_image_label = train_labels[index];

    return make_tuple(matched_image_label, underThreshold);
}

tuple<int, int, int, int> Testing::computeMetrics( Mat train_weights,
                                          vector<QString> train_labels,
                                          Mat test_matrix,
                                          vector<QString> test_labels,
                                          Mat meanVector,
                                          Mat eigenFaces) {

    QString matched_image_label;
    bool match= false;
    int true_positive = 0;
    int false_positive = 0;
    int true_negative = 0;
    int false_negative = 0;
    bool underThreshold = false;


    for(int i=0; i<test_matrix.cols; i++){


        tuple<QString, bool> myTuple = Testing::predict(train_weights, train_labels, test_matrix.col(i), meanVector, eigenFaces);

        matched_image_label = get<0>(myTuple);

        underThreshold = get<1>(myTuple);

        qDebug()<<matched_image_label <<test_labels[i];

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
