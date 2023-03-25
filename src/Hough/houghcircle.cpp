/******************************************************************************
 *
 * File Name: houghcircle.cpp
 * Description: Source file for Circle Detection using Hough Transfrom Class
 * Author(s): Omina Sayed
 * Last Modified: 25 Mar 23 - 02:09
 *
 *******************************************************************************/

#include "houghcircle.h"


int HoughCircle::maxradius = 35;
int HoughCircle::minradius = 9;
int HoughCircle::radius = HoughCircle::maxradius;

int HoughCircle::Xc, HoughCircle::Yc;
vector <Vec3f> HoughCircle::circles;

HoughCircle::HoughCircle()
{

}

// Function to manipulate threshold parameters and perform Canny edge detection
Mat HoughCircle:: Accumulate(Mat SrcImg, int maxradius, int minradius)
{
  //    raduis = maxradius;
  cent accumul[maxradius];
  // Array of structs to store center points
  Mat SrcImgGray, Acc, Edges;
  cvtColor( SrcImg, SrcImgGray, COLOR_BGR2GRAY);
  Acc.create(SrcImgGray.size(), SrcImgGray.type());
  blur( SrcImgGray, Edges, Size(3,3));
  Canny( Edges, Edges, 90, 270, 3);
  // looping over the canny adges to create the accumelator
  for(int i = 0;i < Acc.rows; i++)
    {
      for(int j = 0; j < Acc.cols; j++)
        {
          if (Edges.at<uchar>(i,j) > 256/3)//if edge intensity is stronger than a certain value we add it to the accumaltor
            {
              for (int theta = 0; theta <= 360; theta++)			// Calculating center points for each edge point
                {
                  Xc = i + (radius * cos(theta*PI/180));
                  Yc = j + (radius * sin(theta*PI/180));
                  if(Xc < Acc.rows && Yc < Acc.cols && Xc > 0 && Yc > 0)
                    {
                      Acc.at<uchar>(Xc,Yc) = Acc.at<uchar>(Xc,Yc) + 1;	// Incrementing center point values
                    }
                }
            }
        }
    }

  int votes = 0;						// Highest pixel intensity value
  int Xbright = 0;					// X-index of highest pixel intensity value
  int Ybright = 0;					// Y-index of highest pixel intensity value
  int sum = 0;						// Sum of differences between candidate center point and its neighbors + candidate center point intensity value
  int bigsum = 0;						// Largest sum of differences between candidate center point and its neighbors + candidate center point intensity value
  for(int i = 0; i < Acc.rows; i++)
    {
      for(int j = 0; j < Acc.cols; j++)
        {
          sum += Acc.at<uchar>(i,j);						// Adding candidate center point's intensity value to sum
          if(sum > bigsum)									// Finding largest sum
            {
              accumul[radius].bright = Acc.at<uchar>(i,j);	// Storing corresponding center point in array of structs
              accumul[radius].Xbright = i;
              accumul[radius].Ybright = j;
              votes = Acc.at<uchar>(i,j);					// Storing corresponding center point in variables for quicker access and readability
              Xbright = i;
              Ybright = j;
              bigsum = sum;									// Updating largest sum of differences
            }
          sum = 0;											// Resetting sum of differences
        }
    }
  //    cout<<"Center: "<<"["<<Xbright<<","<<Ybright<<"]"<<"	Votes: "<<votes<<"		Radius:"<<radius<<endl;	// Printing accumulator center point for this radius
  double dist;											// Distance between two points
  double radco = 1;									// Radial coefficient (used to calculate minimum distance between centers)
  bool valid = true;										// Valid/Invalid center point
  Point center(Ybright, Xbright);
  for (int i = maxradius; i > radius ; i--)				// Calculating distance between candidate center point and previously found center points
    {
      dist = sqrt(pow((double(accumul[radius].Xbright - accumul[i].Xbright)), 2) + pow((double(accumul[radius].Ybright - accumul[i].Ybright)), 2));
      if (dist < radco*i)									// If distance between candidate center point and any previous center point is less than the radial coefficient multiplied by any of the previously found radii, it is not a valid center point
        {
          valid = false;									// Set valid to false
        }
    }
  if (valid == true)										// If the center point is valid, draw the corresponding circle
    {
      circle( SrcImg, center, 3, Scalar(0,255,0), -1, 8, 0 );		// Draw circle center point
      circle( SrcImg, center, radius, Scalar(0,0,255), 3, 8, 0 );	// Draw circle outline
    }
  Acc = Scalar::all(0);
  // Reset accumulator to zero
  return SrcImg;
}

Mat HoughCircle::HoughCircleCall(Mat HoughCircle , int minRaduis = 10, int maxRaduis = 35)
{
  Mat imageCircles = HoughCircle.clone();

  for(radius = maxradius; radius > minradius; radius--)							// Varying radial values
    {
      imageCircles = Accumulate(imageCircles, maxRaduis, minRaduis);															// Creating an accumulator for every radial value
      waitKey(1);																// Causing a delay to allow image in trackbar to render
    }
  return imageCircles;
}

