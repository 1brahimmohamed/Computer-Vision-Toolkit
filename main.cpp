#include "src/UI/mainwindow.h"
#include <QApplication>


#include <opencv2/opencv.hpp>
#include <src/FaceRecognition/imagepreproccessing.h>
#include <src/FaceRecognition/pca.h>
#include <src/Testing/testing.h>


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  MainWindow w;
  w.show();

//    vector<QString> trainingLabels;
//    vector<QString> testingLabels;

//    vector<QString> trainingPaths = ImagePreproccessing::readImagesPath("D:/My PC/Projects/Computer-Vision-Toolkit/images/TeamPhotos/faces/Training",
//                        trainingLabels);

//    vector<QString> testingPaths = ImagePreproccessing::readImagesPath("D:/My PC/Projects/Computer-Vision-Toolkit/images/TeamPhotos/faces/Testing",
//                        testingLabels);

//    vector<Mat> trainingImages;
//    vector<Mat> testImages;

//    for(auto path : trainingPaths){
//        trainingImages.push_back(cv::imread(path.toStdString()));
//    }

//    for(auto path : testingPaths){
//        testImages.push_back(cv::imread(path.toStdString()));
//    }

//    Mat flatTrainingImages = ImagePreproccessing::FlattenImages(trainingImages);

//    Mat flatTestImages = ImagePreproccessing::FlattenImages(testImages);

//    Mat meanVector;

//    Mat NormalizedImages = ImagePreproccessing::normalizeImages(flatTrainingImages, meanVector);

//    Mat covMatrix = Pca::calculateCovarianceMatrix(NormalizedImages);

//    qDebug()<<"covMat";

//    Mat eigenFaces = Pca::computePca(covMatrix, NormalizedImages);

//    qDebug()<<"faces";

//    Mat eigenWeights = Pca::computeWeights(eigenFaces, NormalizedImages);

//    qDebug()<<"Weights";

//    ImagePreproccessing::saveMatricesToJson(eigenFaces, eigenWeights, meanVector, "D:/My PC/Projects/Computer-Vision-Toolkit/src/Assets/model.json");

//    Mat newEign, newWei, newMeanVec;
//    ImagePreproccessing::loadMatricesFromJson(newEign,
//                                              newWei,
//                                              newMeanVec,
//                                              "D:/My PC/Projects/Computer-Vision-Toolkit/src/Assets/model.json");

//    qDebug()<<"save";

//    auto [true_positive, false_positive, true_negative, false_negative] = Testing::computeMetrics(eigenWeights, trainingLabels, flatTestImages, testingLabels, meanVector, eigenFaces);

//    qDebug()<<true_positive<< false_positive<< true_negative<< false_negative;

  return a.exec();
}
