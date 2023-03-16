# CV-A01: Images, Filters, Histograms, Gradients, Frequency

## Table of contents:
- [Objectives](#Objectives)
- [Project Features](#deiverablesfolders)
- [Versions](#versions)
- [How to Run The Project](#run-the-project)
- [Team]()

## Objectives
- Filtration of noisy images using low pass filters such as: average, Gaussian, median.
- Edge detection using variety of masks such as: Sobel, Prewitt, and canny edge detectors.
- Histograms and equalization.
- Frequency domain filters.
- Hybrid images.


## Deliverables Folders
- Filters : this includes implementation for filtration functions (requirements 1-3)
    - edgedetectors.cpp/.h
    - noiseaddiatves.cpp/.h
    - imagesmoothers.cpp/ .h

- Frequency : this includes implementation for histogram related tasks (requirements 4-8).
    - fouriermixer.cpp/ .h

- Histograms : this includes implementation for frequency domain related tasks (requirements 9-10).
    - histograms.cpp /.h
- Helpers : this includes the helper functions used in program like converting images to view them or the image class we made it.
    - helperfunctions.cpp/ .h
    - image.cpp/ .h
- Images : folder contains images to implementation.

- UI files: has the ui files
    - mainwindow.cpp/ .h

## Dependenices
    - Qt Version 6.4.2
    - OpenCV 4.7.0

## How to run the project
- Download and Install Qt from the online installer using minGW 64 architecture.
```
https://www.qt.io/download-qt-installer?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4 
```
make sure that QtCharts is enabled

- Download and build openCV 4.7.0 from their website
```
https://opencv.org/releases/
```
- if you don't know how to build openCV on your PC please refer to the installCV.md

- Go to the project.pro file and make sure that openCV libraries are refered to in your pc like that.
``` 
INCLUDEPATH += <yourCV build folder path>\install\include

LIBS += -L<yourCV build folder path>\release\lib \
    -lopencv_calib3d470 \
    -lopencv_core470 \
    -lopencv_features2d470 \
    -lopencv_flann470 \
    -lopencv_highgui470 \
    -lopencv_imgproc470 \
    -lopencv_imgcodecs470 \
    -lopencv_photo470 \
    -lopencv_stitching470 \
    -lopencv_ts470 \
    -lopencv_video470 \
    -lopencv_videoio470 \
```

- Build the project
- Run the project


### Project Overview

### Team

Second Semester - Computer Vision (SBE3230) class project created by:

| Team Members' Names                                       | Section | B.N. |
|---------------------------------------------------------- |:-------:|:----:|
| [Ibrahim Mohamed](https://github.com/1brahimmohamed)      |    1    |  2   |
| [Mahmoud Yaser](https://github.com/mahmoud1yaser)         |    2    |  30  |
| [Maye Khaled](https://github.com/mayekhaled0)             |    2    |  40  |
| [Marina Nasser](https://github.com/MariamWaell)           |    2    |  12  |
| [Omnia Sayed](https://github.com/MariamWaell)             |    1    |  14  |


### Submitted to:
- Eng. Peter Emad & Eng. Laila Abbas
All rights reserved © 2022 to Team 5 - Systems & Biomedical Engineering, Cairo University (Class 2024)