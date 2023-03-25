# CV-A02
## Objectives
* Apply Hough transform for detecting parametric shapes like circles and lines
* Apply Harris operator for detecting corners.
* Apply Active Contour Model for semi-supervised shape delineation.

## Requirements
* Detect edges using Canny edge detector, detect lines and circles located in these images (if any) using Hough transform. Superimpose the detected shapes on the images.
* Initialize the contour for a given object and evolve the Active Contour Model (snake) using the greedy algorithm. Represent the output as chain code and compute the perimeter and the area inside these contours.

### Create two python files to organize your implementation
* **Hough.py**: this will include your implementation for Hough transform for lines and circles (requirement 1).
* **ActiveContour.py**: this will include your implementation for Harris operator for corners detection (requirement 2)

## Important notes:
* You should implement these tasks without depending on OpenCV library or alike. However you can use the OpenCV Canny Edge Detector as preprocessing to Hough Transform.
* Plagiarizing lines will not be tolerated.
* You can start from the source code you delivered from the previous task so that you give your program a new version with new features so that by the end of the semester you will have your own application with multiple computer vision algorithms up and running. (optional)
* Don't forget to upload the report via github.
