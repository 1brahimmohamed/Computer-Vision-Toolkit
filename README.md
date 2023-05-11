# CV-Toolbox: Filters, Histograms, Gradients, Frequency, Contours

## Table of contents:
- [Objectives](#Features)
- [Project Features](#deliverables-folders)
- [Dependinces](#dependenices)
- [How to Run The Project](#how-to-run-the-project)
- [Project Overview](#project-overview)
- [Team](#team)

## Features
- Add various noise types to images such as uniform, guassian & salt-pepper noise.
- Filtration of noisy images using low pass filters such as: average, Gaussian, median filters.
- Edge detection using variety of masks such as: Sobel, Prewitt, Roberts and canny edge detectors.
- Change RGB images to grayscale
- View histograms of images and show equalization & normalization of image.
- Add frequency domain filters such as low-pass, high-pass & Gaussian filters.
- Mix images in frequency domain to get Hybrid images.
- Apply Hough transform for detecting parametric shapes like circles, ellipses and lines
- Apply Active Contour Model for semi-supervised shape delineation.
- Extract the unique features in all images using Harris
operator
- Generate feature descriptors using scale invariant features
(SIFT).
- Match the image set features using sum of squared differences (SSD) and normalized cross correlations (NCC).
- Apply thresholding using optimal thresholding, Otsu, spectral thresholding (more than 2 modes), local & global thresholding.
- Do unspervised segmentation using k-means, region growing, agglomerative and mean shift methods.
- Detect faces (color or grayscale)
- Recognize faces based on PCA/Eigen analysis



## Toolkit Folders

- ActiveContours: Includes active contours class related codes
    - active_contour.cpp /.h
    - image.cpp /.h
    - utils.cpp/.h

- FaceRegonsition: Includes face detection and recognistion code including pca and eigen analysis
    - detectFaces.cpp /.h

- Filters : Includes implementation for filtration functions (requirements 1-3)
    - edgedetectors.cpp/.h
    - noiseaddiatves.cpp/.h
    - imagesmoothers.cpp/ .h
    - threshold.cpp/ .h

- Frequency : Includes implementation for frequency domain related tasks 
    - fouriermixer.cpp/ .h

- Harris: Includes Harris Corner Operator Class
    - harrisoperator.cpp/ .h

- Helpers : Includes the helper functions used all over program like converting images to view them.
    - helperfunctions.cpp/ .h

- Histograms : Includes implementation for histogram related tasks.
    - histograms.cpp/ .h

- Hough: Includes implementation classes of hough transform of Lines, Circles & Ellipses
    - houghcircle.cpp/ .h
    - houghellipse.cpp/ .h
    - houghline.cpp/ .h

- Segementation: Includes segementation classes
    - kmeanssegmentation.cpp/ .h
    - meanshift.cpp/ .h
    - agglomerative.cpp/.h
    - regiongrowing.cpp/ .h

- SSD_NCC: Includes SIFT & image matching classes
    - ssd_ncc.cpp/ .h

- Thresholding: Includes Thresholding related tasks
    - Thresholding.cpp/ .h

- UI files: has the ui files
    - mainwindow.cpp/ .h/ .ui
    - filterwidget.cpp/ .h/ .ui
    - histogramswidget.cpp/ .h/ .ui
    - houghwidget.cpp/ .h/ .ui
    - mixingwidget.cpp/ .h/ .ui
    - facerecognitionwidget.cpp/ .h/ .ui
    - matchingWidget.cpp/ .h/ .ui
    - segementationWidget.cpp/ .h/ .ui

- Assets : folder contains program assets like UI SVGs, images to test implementation & Cascading Face Classifer xml file.

## Dependenices
    - Qt Version 6.4.2
    - Qt Charts
    - OpenCV 4.7.0

## How to run the project
- Download and Install Qt from the online installer using minGW 64 architecture.
```
www.qt.io
```
make sure that QtCharts is enabled

- Download and build openCV 4.7.0 from their website
```
www.opencv.org/releases/
```
- if you don't know how to build openCV on your PC please refer to the installCV.md

- Go to the project.pro file and make sure that openCV libraries are refered to in your pc like that.
``` 
INCLUDEPATH += <yourCV build folder path>\install\include

LIBS += -L<yourCV build folder path>\release\lib \
    -lopencv_calib3d470                 \
    -lopencv_core470                    \
    -lopencv_features2d470              \
    -lopencv_flann470                   \
    -lopencv_highgui470                 \
    -lopencv_imgproc470                 \
    -lopencv_imgcodecs470               \
    -lopencv_photo470                   \
    -lopencv_stitching470               \
    -lopencv_ts470                      \
    -lopencv_video470                   \
    -lopencv_videoio470                 \
    -lopencv_objdetect470               \
```

- Build the project
- Run the project


### Project Overview
- Filters Tab
![Filters Tab](./images/newgifs/1.gif)
- Hybrid Image Tab
![GrayScale Tab](./images/newgifs/2.gif)
- Histograms Tab
![Histogram Tab](./images/newgifs/3.gif)
- Hough Trasform & Active Contours Tab
![Hough Tab](./images/newgifs/4.gif)
- Harris & SIFT Tab
![Harris & SIFT Tab](./images/newgifs/5.gif)
- Segementation Tab
![Segementation Tab](./images/newgifs/6.gif)
Face Detection & Recognistion Tab
![Face Detection Tab](./images/newgifs/7.gif)


### Team

Second Semester - Computer Vision (SBE3230) class project created by:

| Team Members' Names                                       | Section | B.N. |
|---------------------------------------------------------- |:-------:|:----:|
| [Ibrahim Mohamed](https://github.com/1brahimmohamed)      |    1    |  2   |
| [Mahmoud Yaser](https://github.com/mahmoud1yaser)         |    2    |  30  |
| [Maye Khaled](https://github.com/mayekhaled0)             |    2    |  40  |
| [Marina Nasser](https://github.com/MarinaNasser)          |    2    |  12  |
| [Omnia Sayed](https://github.com/omniaSayed)              |    1    |  14  |


### Submitted to:
- Eng. Peter Emad & Eng. Laila Abbas
All rights reserved © 2022 to Team 5 - Systems & Biomedical Engineering, Cairo University (Class 2024)