#include "meanshift.h"

const int dxdy[][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};	// Region Growing

MeanShift::MeanShift()
{

}

void MeanShift::setPixelData(PixelDataContainer* pixel, float pixelX, float pixelY, float pixelL, float pixelU, float pixelV){
  pixel->x = pixelX;
  pixel->y = pixelY;
  pixel->l = pixelL;
  pixel->u= pixelU;
  pixel->v = pixelV;
}

void MeanShift::setUpLUVPixel(PixelDataContainer* pixel){
  pixel->l = pixel->l * 100 / 255;
  pixel->u = pixel->u - 128;
  pixel->v = pixel->v - 128;
}

void MeanShift::setUpRGBPixel(PixelDataContainer* pixel){
  pixel->l = pixel->l * 255 / 100;
  pixel->u = pixel->u + 128;
  pixel->v = pixel->v + 128;
}

float MeanShift::CalculateColorDistance(PixelDataContainer pixel1, PixelDataContainer pixel2){
  return sqrt((pixel1.l - pixel2.l) * (pixel1.l - pixel2.l) + (pixel1.u - pixel2.u) * (pixel1.u - pixel2.u) + (pixel1.v - pixel2.v) * (pixel1.v - pixel2.v));
}

float MeanShift::CalculateSpatialDistance(PixelDataContainer pixel1, PixelDataContainer pixel2){
  return sqrt((pixel1.x - pixel2.x) * (pixel1.x - pixel2.x) + (pixel1.y - pixel2.y) * (pixel1.y - pixel2.y));
}

void MeanShift::MuliplyPixelDataByScale(PixelDataContainer* pixel, float scale){
  pixel->x *= scale;
  pixel->y *= scale;
  pixel->l *= scale;
  pixel->u *= scale;
  pixel->v *= scale;
}

void MeanShift::addPixels(PixelDataContainer* mainPixel, PixelDataContainer pixelAdded){
  mainPixel->x += pixelAdded.x;
  mainPixel->y += pixelAdded.y;
  mainPixel->l += pixelAdded.l;
  mainPixel->u += pixelAdded.u;
  mainPixel->v += pixelAdded.v;
}

void MeanShift::copyPixel(PixelDataContainer* pixelCopyingTo, PixelDataContainer* pixelCopyingFrom){
  pixelCopyingTo->x = pixelCopyingFrom->x;
  pixelCopyingTo->y = pixelCopyingFrom->y;
  pixelCopyingTo->l = pixelCopyingFrom->l;
  pixelCopyingTo->u = pixelCopyingFrom->u;
  pixelCopyingTo->v = pixelCopyingFrom->v;
}

Mat MeanShift::MeanShiftSegmentation(Mat Img, float distanceBandwidth, float colorBandwidth){

  Mat ImgOut = Img.clone();
  cvtColor(ImgOut, ImgOut, COLOR_BGR2Luv);

  int ROWS = Img.rows;
  int COLS = Img.cols;
  vector<Mat> IMGChannels(3);
  split(ImgOut, IMGChannels);

  PixelDataContainer PtCur;
  PixelDataContainer PtPrev;
  PixelDataContainer PtSum;
  PixelDataContainer Pt;

  int Left;
  int Right;
  int Top;
  int Bottom;
  int NumPts;
  int step;

  for(int i = 0; i < ROWS; i++){
      for(int j = 0; j < COLS; j++){
          Left = (j - distanceBandwidth) > 0 ? (j - distanceBandwidth) : 0;
          Right = (j + distanceBandwidth) < COLS ? (j + distanceBandwidth) : COLS;
          Top = (i - distanceBandwidth) > 0 ? (i - distanceBandwidth) : 0;
          Bottom = (i + distanceBandwidth) < ROWS ? (i + distanceBandwidth) : ROWS;
          setPixelData(&PtCur, i, j, (float)IMGChannels[0].at<uchar>(i, j), (float)IMGChannels[1].at<uchar>(i, j), (float)IMGChannels[2].at<uchar>(i, j));
          setUpLUVPixel(&PtCur);
          step = 0;
          do{
              copyPixel(&PtPrev, &PtCur);
              setPixelData(&PtSum, 0, 0, 0, 0, 0);
              NumPts = 0;
              for(int hx = Top; hx < Bottom; hx++){
                  for(int hy = Left; hy < Right; hy++){

                      setPixelData(&Pt, hx, hy, (float)IMGChannels[0].at<uchar>(hx, hy), (float)IMGChannels[1].at<uchar>(hx, hy), (float)IMGChannels[2].at<uchar>(hx, hy));
                      setUpLUVPixel(&Pt);

                      if(CalculateColorDistance(Pt, PtCur) < colorBandwidth){
                          addPixels(&PtSum, Pt);
                          NumPts++;
                        }
                    }
                }
              MuliplyPixelDataByScale(&PtSum, 1.0 / NumPts);
              copyPixel(&PtCur, &PtSum);
              step++;
            }while((CalculateColorDistance(PtCur, PtPrev) > TOLERANCE_COLOR) && (CalculateSpatialDistance(PtCur, PtPrev) > TOLERANCE_SPATIAL) && (step < MAX_CONVERGENCE_ITRS));

          setUpRGBPixel(&PtCur);
          ImgOut.at<Vec3b>(i, j) = Vec3b(PtCur.l, PtCur.u, PtCur.v);
        }
    }

  //----------------------- Segmentation ------------------------------

  int label = -1;                                                       // Label number
  vector<float> Mode(ROWS * COLS * 3);					// Store the Lab color of each region
  vector<int> MemberModeCount(ROWS * COLS, 0);				// Store the number of each region
  split(ImgOut, IMGChannels);
  // Label for each point
  vector<vector<int>> Labels(ROWS);;

  // Initialization
  for(int i = 0; i < ROWS; i++){
      for(int j = 0; j < COLS; j++){
          Labels[i].push_back(-1);
        }
    }

  for(int i = 0; i < ROWS; i++){
      for(int j = 0; j < COLS;j ++){
          // If the point is not being labeled
          if(Labels[i][j] < 0){
              Labels[i][j] = ++label;		// Give it a new label number
              // Get the point
              setPixelData(&PtCur, i, j, (float)IMGChannels[0].at<uchar>(i, j), (float)IMGChannels[1].at<uchar>(i, j), (float)IMGChannels[2].at<uchar>(i, j));
              setUpLUVPixel(&PtCur);

              // Store each value of Lab
              Mode[label * 3 + 0] = PtCur.l;
              Mode[label * 3 + 1] = PtCur.u;
              Mode[label * 3 + 2] = PtCur.v;

              // Region Growing 8 Neighbours
              vector<PixelDataContainer> NeighbourPoints;
              NeighbourPoints.push_back(PtCur);
              while(!NeighbourPoints.empty()){
                  Pt = NeighbourPoints.back();
                  NeighbourPoints.pop_back();

                  // Get 8 neighbours
                  for(int k = 0; k < 8; k++){
                      int hx = Pt.x + dxdy[k][0];
                      int hy = Pt.y + dxdy[k][1];
                      if((hx >= 0) && (hy >= 0) && (hx < ROWS) && (hy < COLS) && (Labels[hx][hy] < 0)){
                          PixelDataContainer P;
                          setPixelData(&P, hx, hy, (float)IMGChannels[0].at<uchar>(hx, hy), (float)IMGChannels[1].at<uchar>(hx, hy), (float)IMGChannels[2].at<uchar>(hx, hy));
                          setUpLUVPixel(&P);

                          // Check the color
                          if(CalculateColorDistance(PtCur, P) < colorBandwidth){
                              // Satisfied the color bandwidth
                              Labels[hx][hy] = label;				// Give the same label
                              NeighbourPoints.push_back(P);		// Push it into stack
                              MemberModeCount[label]++;			// This region number plus one
                              // Sum all color in same region
                              Mode[label * 3 + 0] += P.l;
                              Mode[label * 3 + 1] += P.u;
                              Mode[label * 3 + 2] += P.v;
                            }
                        }
                    }
                }
              MemberModeCount[label]++;							// Count the point itself
              Mode[label * 3 + 0] /= MemberModeCount[label];		// Get average color
              Mode[label * 3 + 1] /= MemberModeCount[label];
              Mode[label * 3 + 2] /= MemberModeCount[label];
            }
        }
    }
  // Get result image from Mode array
  for(int i = 0; i < ROWS; i++){
      for(int j = 0; j < COLS; j++){
          label = Labels[i][j];
          float l = Mode[label * 3 + 0];
          float a = Mode[label * 3 + 1];
          float b = Mode[label * 3 + 2];
          PixelDataContainer Pixel;
          setPixelData(&Pixel, i, j, l, a, b);
          setUpRGBPixel(&Pixel);
          ImgOut.at<Vec3b>(i, j) = Vec3b(Pixel.l, Pixel.u, Pixel.v);
        }
    }
  cvtColor(ImgOut, ImgOut, COLOR_Luv2BGR);
  return ImgOut;
}
