#include "src/UI/mainwindow.h"
#include <QApplication>


#include <opencv2/opencv.hpp>
#include <src/FaceRecognition/imagepreproccessing.h>



int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  //    MainWindow w;
  //    w.show();

  ImagePreproccessing *obj = new ImagePreproccessing();

    Mat img1 = imread("D:\\My PC\\Projects\\Computer-Vision-Toolkit\\images\\TeamPhotos\\faces\\Ibrahim_detected00.jpg");
    Mat img12 = imread("D:\\My PC\\Projects\\Computer-Vision-Toolkit\\images\\TeamPhotos\\faces\\Ibrahim_detected01.jpg");
    Mat img13 = imread("D:\\My PC\\Projects\\Computer-Vision-Toolkit\\images\\TeamPhotos\\faces\\Ibrahim_detected02.jpg");
    Mat img14 = imread("D:\\My PC\\Projects\\Computer-Vision-Toolkit\\images\\TeamPhotos\\faces\\Ibrahim_detected03.jpg");

    vector<Mat> tag = {img1, img12,img13, img14};

    Mat flat = obj->FlattenImages(tag);
  //  imshow("before mean", flat);

  // ------------------------------------------------------------------------

//  vector<QString> labelss;
//  vector<QString> paths = obj->readImagesPath("D:/My PC/Projects/Computer-Vision-Toolkit/images/TeamPhotos/faces", labelss);

//  for(int i = 0; i < labelss.size(); i++){
//      qDebug() << paths[i];
//      qDebug() << labelss[i];
//    }
  // ------------------------------------------------------------------------

    Mat mean;
    Mat norma = obj->normalizeImages(flat, mean);
//    imshow("after mean minus", norma);

  //  Mat cov = obj->CalculateCovarianceMatrix(norma);
  //  imshow("cov", cov);
//    Mat img15 = imread("D:\\My PC\\Projects\\Computer-Vision-Toolkit\\images\\TeamPhotos\\faces\\Ibrahim_detected04.jpg");
//    Mat normalized = obj->imageNormalization(img15, mean);
//    qDebug("ytes");

//    imshow("after mean minus one image", normalized);

    QString filePath = "D:/My PC/Projects/Computer-Vision-Toolkit/src/Assets/hima.json";

    obj->saveMatricesToJson(mean, mean, filePath);

    Mat newWei, newMean;
    obj->loadMatricesFromJson(newWei, newMean, "D:/My PC/Projects/Computer-Vision-Toolkit/src/Assets/hima.json");

  return a.exec();
}
