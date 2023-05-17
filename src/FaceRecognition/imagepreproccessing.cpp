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

vector<QString> ImagePreproccessing::readImagesPath(){
  vector<QString> imagesPaths;
  QDir inputDir(this->inputFolderPath);
  QString path;
  for (const auto& fileInfo : inputDir.entryInfoList())
    {
      if (fileInfo.isFile() && fileInfo.suffix().toLower() == "jpg")
        {
          path = fileInfo.filePath();
          imagesPaths.push_back(path);
        }
    }
  return imagesPaths;
}

Mat ImagePreproccessing::FlattenImages(vector<Mat> images){
  // initialize the flatten images matrix and the vector of flatten images
  Mat flattenImages;
  vector<Mat> vectorOfFlatMats;

  // loop through all images and flatten them
  for(auto& image: images){
      Mat grayImage;
      cvtColor(image, grayImage, COLOR_BGR2GRAY);       // convert the image to gray scale
      Mat flattenGrayImage = grayImage.reshape(1, 1);   // flatten the image
      vectorOfFlatMats.push_back(flattenGrayImage);     // add the flatten image to the vector of flatten images
    }

  // concatenate all flatten images into one matrix
  vconcat(vectorOfFlatMats, flattenImages);

  // transpose the flatten images matrix
  return flattenImages.t();
}

Mat ImagePreproccessing::normalizeImages(Mat flattenImages, Mat &sentMean){
  // initialize the normalized images matrix
  vector<Mat> normalizedImages;

  // calculate the mean column vector of the flatten images matrix
  Mat mean;

  // get the mean of each row to form a vector col mean (1 is the col direction and 0 is row)
  cv::reduce(flattenImages, mean, 1, REDUCE_AVG);
  sentMean = mean;

  Mat result;
  sentMean = mean;
  // subtract the mean from each column
  for (int i = 0; i < flattenImages.cols; i++)
    {
      normalizedImages.push_back(flattenImages.col(i) - mean);
    }

  // concatenate all normalized cols into one matrix
  hconcat(normalizedImages, result);

  return result;
}

Mat ImagePreproccessing::CalculateCovarianceMatrix(Mat normalizedImages){
  // initialize the covariance matrix

  // get the transpose of the normalized images matrix
  Mat normalizedImagesT;
  transpose(normalizedImages, normalizedImagesT);

  qDebug() << normalizedImages.rows << normalizedImages.cols;
  qDebug() << normalizedImagesT.rows << normalizedImagesT.cols;


  Mat covarianceMatrix, mu;

  // calculate the covariance matrix
  cv::calcCovarMatrix(normalizedImages, covarianceMatrix, mu, COVAR_NORMAL | cv::COVAR_ROWS);

  covarianceMatrix /= static_cast<double>(normalizedImages.cols - 1);

  qDebug() << "Covariance Matrix Shape: " << covarianceMatrix.rows <<  covarianceMatrix.cols;

  return covarianceMatrix;
}

Mat ImagePreproccessing::computeEign(Mat covarianceMatrix, Mat& eigenVals){
//  Mat eigenVectors;

//  eigen(covarianceMatrix,eigenVals ,eigenVectors);

//  return oneMatSortedEigenVectors;
}

