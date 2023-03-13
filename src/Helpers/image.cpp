#include "image.h"

Image::Image()
{
  this->kenerlSize = 5;
  this->sigma = 1.0;

  this->Original = NULL;
  this->Current = NULL;
  this->Filtered = NULL;
  this->Previous = NULL;
  this->Next = NULL;
}

void Image::setFirstUpload(Mat image){
  this->Original = image;
  this->Current = image;
}

void Image::setFilteredImage(Mat image){
  this->Filtered = image;
}

void Image::setPreviousActionImage(Mat image){
  this->Previous = image;
}

void Image::setNextActionImage(Mat image){
  this->Next = image;
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

Mat Image::getPreviousActionImage(){
  return this->Previous;
}

Mat Image::getNextActionImage(){
  return this->Next;
}
