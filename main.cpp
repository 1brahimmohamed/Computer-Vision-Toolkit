#include "src/UI/mainwindow.h"
#include <QApplication>


#include <opencv2/opencv.hpp>




int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

/* Code to run active_contours
 * Parameters Needed:
 * Alpha (0.1-10) float 0.1
 * Beta (0.1-10) float 0.1
 * Gamma (1-50) int 1
 * Radius (1-500) int 1
 * Points (50-300) int 10
 * Iterations (1-100) int 1
*/
 return a.exec();
}
