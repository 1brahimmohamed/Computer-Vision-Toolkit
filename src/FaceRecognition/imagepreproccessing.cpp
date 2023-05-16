#include "imagepreproccessing.h"
#include "src/FaceRecognition/detectFaces.h"

#include <QDir>

ImagePreproccessing::ImagePreproccessing()
{
  // Get Current Dir Path
  this->currentDir = QDir::current();
  // go to the parent dir of the current dir
  this->currentDir.cdUp();

  this->inputFolderPath = this->currentDir.absoluteFilePath("Computer-Vision-Toolkit/images/TeamPhotos/");
  this->outputFolderPath = this->currentDir.absoluteFilePath("Computer-Vision-Toolkit/images/TeamPhotos/faces");

  // Load Cascade Classifer
  this->classiferFilePath = this->currentDir.absoluteFilePath("Computer-Vision-Toolkit/src/Assets/cascadeFaceClassifier.xml");
  this->cascade.load(this->classiferFilePath.toStdString());
}

void ImagePreproccessing::DetectFacesInFolder(){

  // Create the output folder if it doesn't exist
  QDir outputDir(this->outputFolderPath);
  if (!outputDir.exists())
  {
      outputDir.mkpath(".");
  }

  unsigned int counter = 0;

  // Loop through all files in the input folder
  QDir inputDir(this->inputFolderPath);
  for (const auto& fileInfo : inputDir.entryInfoList())
  {
      if (fileInfo.isFile() && fileInfo.suffix().toLower() == "jpg")
      {
          // Load the input image,
          Mat inputImage = cv::imread(fileInfo.filePath().toStdString());

          vector<Mat> outFaces;

          bool isFace = DetectFaces::detectFaces(this->cascade, inputImage, outFaces);

          if(isFace){
              QString outputFilename;
              unsigned int count = 0;
              QString everyPicName;

              for(auto& face: outFaces){
                  // Save the detected face as a new image
                  outputFilename = this->outputFolderPath + "/" + "Marina" + "_detected" + QString::number(count) + QString::number(counter)+".jpg";
                  cv::imwrite(outputFilename.toStdString(), face);
                  count++;
                }
            }
          counter++;

      }
  }
}
