#include "imagepreproccessing.h"
#include "src/FaceRecognition/detectFaces.h"
#include "src/FaceRecognition/pca.h"
#include "src/Testing/testing.h"

#include <QDir>

#define NUM_EIGEN_FACES 30

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

QString ImagePreproccessing::getLabelFromImagePath(QString imagePath){

  QString label = imagePath;
  QString fileName = QFileInfo(imagePath).fileName();

  if (fileName.contains("Ibrahim"))
    label = "Ibrahim";
  else if (fileName.contains("Marina"))
    label = "Marina";
  else if (fileName.contains("Mahmoud"))
    label = "Mahmoud";
  else if (fileName.contains("Maye"))
    label = "Maye";
  else if (fileName.contains("Omnia"))
    label = "Omnia";
  else
    label = "Unknown";

  return label;
}

vector<QString> ImagePreproccessing::readImagesPath(QString inputFolder, vector<QString> &labels){
  vector<QString> imagesPaths;
  vector<QString> imgsLabels;

  QDir inputDir(inputFolder);
  QString path;
  for (const auto& fileInfo : inputDir.entryInfoList())
    {
      if (fileInfo.isFile() && fileInfo.suffix().toLower() == "jpg")
        {
          path = fileInfo.filePath();
          imagesPaths.push_back(path);
          imgsLabels.push_back(getLabelFromImagePath(path));
        }
    }
  labels = imgsLabels;
  return imagesPaths;
}

Mat ImagePreproccessing::FlattenImages(vector<Mat> images){
  // initialize the flatten images matrix and the vector of flatten images
  Mat flattenImages(static_cast<int>(images.size()), images[0].rows * images[0].cols * 3, CV_32F);
  vector<Mat> vectorOfFlatMats;

  // loop through all images and flatten them
  for(auto& image: images){
      /*      Mat grayImage;
      cvtColor(image, grayImage, COLOR_BGR2GRAY); */      // convert the image to gray scale
      Mat flattenGrayImage = image.reshape(1, 1);   // flatten the image
      vectorOfFlatMats.push_back(flattenGrayImage);     // add the flatten image to the vector of flatten images
    }

  // concatenate all flatten images into one matrix
  vconcat(vectorOfFlatMats, flattenImages);

  // transpose the flatten images matrix
  return flattenImages;
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
  // subtract the mean from each column
  for (int i = 0; i < flattenImages.cols; i++)
    {
      normalizedImages.push_back(flattenImages.col(i) - mean);
    }

  // concatenate all normalized cols into one matrix
  hconcat(normalizedImages, result);

  return result;
}

Mat ImagePreproccessing::imageNormalization(Mat image, Mat mean){

  Mat normalizedImage;
  cvtColor(image, image, COLOR_BGR2GRAY);
  Mat flattenGrayImage = image.reshape(1, 1);   // flatten the image

  qDebug() << flattenGrayImage.type();
  qDebug() << mean.type();

  cv::subtract(flattenGrayImage.t(), mean, normalizedImage,noArray(), 0);

  return normalizedImage;
}


void ImagePreproccessing::saveMatricesToJson(const cv::Mat eigenFaces, const cv::Mat weights, const cv::Mat mean, const QString filePath) {
  // Create a JSON object
  QJsonObject jsonObject;

  // Convert weights matrix to JSON array
  QJsonArray weightsArray;
  for (int i = 0; i < weights.rows; ++i) {
      QJsonArray rowArray;
      for (int j = 0; j < weights.cols; ++j) {
          rowArray.append(weights.at<double>(i,j));
        }
      weightsArray.append(rowArray);
    }
  jsonObject["weights"] = weightsArray;

  // Convert mean matrix to JSON array
  QJsonArray meanArray;
  for (int i = 0; i < mean.rows; ++i) {
      meanArray.append(mean.at<double>(i, 0));
    }
  jsonObject["mean"] = meanArray;

  // Convert eigenFaces matrix to JSON array
  QJsonArray eigenFacesArray;
  for (int i = 0; i < eigenFaces.rows; ++i) {
      QJsonArray rowArray;
      for (int j = 0; j < eigenFaces.cols; ++j) {
          rowArray.append(eigenFaces.at<double>(i, j));
        }
      eigenFacesArray.append(rowArray);
    }
  jsonObject["eigenFaces"] = eigenFacesArray;

  // Create a JSON document from the JSON object
  QJsonDocument jsonDoc(jsonObject);

  // Save the JSON document to a file
  QFile file(filePath);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      file.write(jsonDoc.toJson());
      file.close();
      qDebug() << "Matrices saved to JSON file: " << filePath;
    } else {
      qDebug() << "Failed to save matrices to JSON file: " << filePath;
    }
}


void ImagePreproccessing::loadMatricesFromJson(cv::Mat& eigenFaces, cv::Mat& weights, cv::Mat &mean, const QString filePath) {
  // Load the JSON file
  QFile file(filePath);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << "Failed to open JSON file: " << filePath;
      return;
    }


  // Read the JSON data from the file
  QByteArray jsonData = file.readAll();
  file.close();

  // Parse the JSON document
  QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
  if (jsonDoc.isNull()) {
      qDebug() << "Failed to parse JSON data";
      return;
    }

  // Get the JSON object from the document
  QJsonObject jsonObject = jsonDoc.object();

  // Read the weights from the JSON array
  QJsonArray weightsArray = jsonObject["weights"].toArray();
  int weightsRows = weightsArray.size();
  int weightsCols = weightsArray[0].toArray().size();

  weights = cv::Mat(weightsRows, weightsCols, CV_64F);

  for (int i = 0; i < weightsRows; ++i) {
      QJsonArray rowArray = weightsArray[i].toArray();
      for (int j = 0; j < weightsCols; ++j) {
          weights.at<double>(i, j) = rowArray[j].toDouble();
        }
    }

  // Read the mean from the JSON array
  QJsonArray meanArray = jsonObject["mean"].toArray();
  int meanSize = meanArray.size();
  mean = cv::Mat(meanSize, 1, CV_64F);
  for (int i = 0; i < meanSize; ++i) {
      mean.at<double>(i, 0) = meanArray[i].toDouble();
    }

  // Read the eigenFaces from the JSON array
  QJsonArray eigenFacesArray = jsonObject["eigenFaces"].toArray();
  int eigenFacesRows = eigenFacesArray.size();
  int eigenFacesCols = eigenFacesArray[0].toArray().size();
  eigenFaces = cv::Mat(eigenFacesRows, eigenFacesCols, CV_64F);
  for (int i = 0; i < eigenFacesRows; ++i) {
      QJsonArray rowArray = eigenFacesArray[i].toArray();
      for (int j = 0; j < eigenFacesCols; ++j) {
          eigenFaces.at<double>(i, j) = rowArray[j].toDouble();
        }
    }

  qDebug() << "Matrices loaded from JSON file: " << filePath;
}



void ImagePreproccessing::training(QString modelPath){

  qDebug() << "Starting Training Process ...";


  vector<QString> trainingLabels;
  vector<QString> testingLabels;


  qDebug() << "Reading Images ...";

  vector<QString> trainingPaths = readImagesPath("D:/My PC/Projects/Computer-Vision-Toolkit/images/TeamPhotos/faces/Training",
                      trainingLabels);

  vector<QString> testingPaths = readImagesPath("D:/My PC/Projects/Computer-Vision-Toolkit/images/TeamPhotos/faces/Testing",
                      testingLabels);

  vector<Mat> trainingImages;
  vector<Mat> testImages;

  for(auto path : trainingPaths){
      trainingImages.push_back(cv::imread(path.toStdString()));
  }

  for(auto path : testingPaths){
      testImages.push_back(cv::imread(path.toStdString()));
  }

  Mat flatTrainingImages = FlattenImages(trainingImages);

  Mat flatTestImages = FlattenImages(testImages);

  Mat meanVector;

  Mat NormalizedImages = normalizeImages(flatTrainingImages, meanVector);

  qDebug() << "Calculating Covariance ...";

  Mat covMatrix = Pca::calculateCovarianceMatrix(NormalizedImages);

  qDebug() << "Computing PCA ...";


  Mat eigenFaces = Pca::computePca(covMatrix, NormalizedImages);

  qDebug() << "Computing Weights ...";

  Mat eigenWeights = Pca::computeWeights(eigenFaces, NormalizedImages);

  saveMatricesToJson(eigenFaces, eigenWeights, meanVector, modelPath);

//  auto [true_positive, false_positive, true_negative, false_negative] = Testing::computeMetrics(eigenWeights, trainingLabels, flatTestImages, testingLabels, meanVector, eigenFaces);

//  qDebug()<<true_positive<< false_positive<< true_negative<< false_negative;
}
