#include "facerecognitionwidget.h"
#include "ui_facerecognitionwidget.h"

#include "src/Helpers/helperfunctions.h"
#include "src/FaceRecognition/detectFaces.h"
#include "src/FaceRecognition/imagepreproccessing.h"
#include "src/Testing/testing.h"

#include<QDebug>

FaceRecognitionWidget::FaceRecognitionWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FaceRecognitionWidget)
{
  ui->setupUi(this);

  // Get Current Dir Path
  this->currentDir = QDir::current();
  // go to the parent dir of the current dir
  this->currentDir.cdUp();

  // Load Cascade Classifer
  this->classiferFilePath = this->currentDir.absoluteFilePath("Computer-Vision-Toolkit/src/Assets/cascadeFaceClassifier.xml");
  this->cascade.load(this->classiferFilePath.toStdString());

  // Load the no face image
  this->noFaceImagePath = this->currentDir.absoluteFilePath("Computer-Vision-Toolkit/src/Assets/UA.jpg");
  noFaceImage = imread(this->noFaceImagePath.toStdString());



  QString modelPath = "D:/My PC/Projects/Computer-Vision-Toolkit/src/Assets/model.json";
  QFile file(modelPath);


  if (!file.exists())
    ImagePreproccessing::training(modelPath);


  ImagePreproccessing::loadMatricesFromJson(this->eigenFaces,
                                            this->weights,
                                            this->meanVector,
                                            modelPath);

  ImagePreproccessing::readImagesPath("D:/My PC/Projects/Computer-Vision-Toolkit/images/TeamPhotos/faces/Training",
                                      this->trainingLabels);

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

void uploadData(){

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

  // detect faces
  bool isPerson = DetectFaces::detectFaces(this->cascade,
                                           this->recognitionWidgetImage.originalImage,
                                           faces);


  // if we found a face
  if (isPerson){
      // Resize input Mats to the same size if necessary
      const cv::Size size(200, 200); // Example size
      for (cv::Mat& face : faces) {
          cv::resize(face, face, size);
          detectedFace = face;
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
  // if we didn't found any faces view the no face image
  else{
      this->updateFilteredPicture(this->noFaceImage);
    }

}

void FaceRecognitionWidget::on_recognitionBtn_clicked()
{
  Mat normalizedImage = ImagePreproccessing::imageNormalization(detectedFace,this->meanVector);

  auto [person, threshold] = Testing::predict(this->weights,
                                              this->trainingLabels,
                                              normalizedImage,
                                              this->meanVector,
                                              this->eigenFaces, 2e8);

  ui->personLabel->setText("I Recognized: " + person);
}

