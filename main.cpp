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
  imshow("before mean", flat);

  // ------------------------------------------------------------------------
  //  vector<QString> paths = obj->readImagesPath();

  //  for(auto path: paths){
  //      qDebug() << path;
  //  }

  Mat mean;
  Mat norma = obj->normalizeImages(flat, mean);
  imshow("after mean minus", norma);

  Mat cov = obj->CalculateCovarianceMatrix(norma);
  imshow("cov", cov);
  
  return a.exec();
}
