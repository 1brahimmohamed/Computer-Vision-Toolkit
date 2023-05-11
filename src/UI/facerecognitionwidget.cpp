#include "facerecognitionwidget.h"
#include "ui_facerecognitionwidget.h"

#include "src/Helpers/helperfunctions.h"
#include "src/FaceRecognition/detectFaces.h"



FaceRecognitionWidget::FaceRecognitionWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FaceRecognitionWidget)
{
  ui->setupUi(this);

  QDir currentDir = QDir::current();
  currentDir.cdUp();
  QString filePath = currentDir.absoluteFilePath("Computer-Vision-Toolkit/src/Assets/cascadeFaceClassifier.xml");
  qDebug() << filePath;
  cascade.load(filePath.toStdString());
}

FaceRecognitionWidget::~FaceRecognitionWidget()
{
  delete ui;
}

// ------------------------------- GENERAL FUNCTIONS ------------------------------------- //

void FaceRecognitionWidget::updateFilteredPicture(Mat updatedImage){
  this->recognitionWidgetImage.detectedFacesImage = updatedImage;
  HelperFunctions::viewImageOnLabel(updatedImage, ui->imageDetected);
}

void FaceRecognitionWidget::on_uploadImageBtn_clicked()
{
  Mat Image = HelperFunctions::readImage_Mat();
  if (Image.cols > 1 && Image.rows >1){
      this->recognitionWidgetImage.originalImage = Image;
      HelperFunctions::viewImageOnLabel(Image,ui->imageOriginal);
    }
}

void FaceRecognitionWidget::on_detectFacesBtn_clicked()
{
  std::vector<cv::Mat> faces;

  bool isPerson = detectFaces(cascade,
                              recognitionWidgetImage.originalImage,
                              faces);

  if (isPerson){
      // Resize input Mats to the same size if necessary
      const cv::Size size(200, 200); // Example size
      for (cv::Mat& face : faces) {
          cv::resize(face, face, size);
        }

      // Calculate the number of rows and columns in the grid
      const int numImages = faces.size();
      const int numRows = static_cast<int>(std::sqrt(numImages));
      const int numCols = (numImages + numRows - 1) / numRows; // Round up

      std::vector<cv::Mat> rows;
      for (int row = 0; row < numRows; ++row) {

          std::vector<cv::Mat> cols;
          for (int col = 0; col < numCols; ++col) {
              const int index = row * numCols + col;
              if (index < numImages) {
                  cols.push_back(faces[index]);
                }
            }
          cv::Mat rowMat;
          cv::hconcat(cols, rowMat);
          rows.push_back(rowMat);
        }
      cv::Mat combined;
      cv::vconcat(rows, combined);

      this->updateFilteredPicture(combined);
    }

}

