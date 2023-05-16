#include "src/UI/mainwindow.h"
#include <QApplication>


#include <opencv2/opencv.hpp>
#include <src/FaceRecognition/imagepreproccessing.h>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//  ImagePreproccessing *obj = new ImagePreproccessing();

//  obj->DetectFacesInFolder();

  return a.exec();
}
