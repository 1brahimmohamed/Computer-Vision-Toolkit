#include "image.h"

Image::Image()
{
  this->kenerlSize = 5;
  this->sigma = 1.0;

  this->Original = NULL;
  this->Current = NULL;
  this->Filtered = NULL;
  this->Normalized = NULL;
}

void Image::setFirstUpload(Mat image){
  this->Original = image;
  this->Current = image;
}

void Image::setFilteredImage(Mat image){
  this->Filtered = image;
}

void Image::setNormalizedImage(Mat image){
  this->Normalized = image;
}

void Image::setCurrentImage(Mat image){
  this->Current = image;
}
Mat Image::getOriginalImage(){
  return this->Original;
}

Mat Image::getCurrentImage(){
  return this->Current;
}

Mat Image::getFilteredImage(){
  return this->Filtered;
}

Mat Image::getNormalizedImage(){
  return this->Normalized;
}
