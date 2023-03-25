#include "image.h"
#include "utils.h"
#include "cvector.h"
#include <opencv2/opencv.hpp>
#include <random>

#define PI 3.14159265
using namespace std;
using namespace cv;

namespace img
{
    Image::Image(cvector<uchar> pixels, size_t rows, size_t cols, int type)
    {
        this->mat = cv::Mat(rows, cols, type);
        memcpy(this->mat.data, pixels.data(), pixels.size() * sizeof(unsigned char));
        this->pixels = pixels;
    }

    Image::Image(cv::Mat mat)
    {
        this->mat = mat;
        this->vectorize();
    }

    void Image::display(std::string title) const
    {
        cv::namedWindow(title, cv::WINDOW_AUTOSIZE);
        cv::imshow(title, this->mat);
        cv::waitKey(0);
    }

    void Image::vectorize()
    {
        if (this->mat.isContinuous())
        {
            this->pixels.assign((unsigned char *)this->mat.datastart, (unsigned char *)this->mat.dataend);
        }
        else
        {
            for (int i = 0; i < this->mat.rows; ++i)
            {
                this->pixels.insert(this->pixels.end(), this->mat.ptr<unsigned char>(i), this->mat.ptr<unsigned char>(i) + this->mat.cols);
            }
        }
    }

    Image noise_filter(Image &source, int size, std::string type, double std)
    {
        cvector<cvector<double>> filter = gaussian_kernel(size, std);
        double pixel_value = 0;
        int limit = size - 1;
        cvector<uchar> sub_matrix;
        cv::Mat source_mat = source.mat.clone();
        int channels_number = source_mat.channels();
        int cols_number = source_mat.cols;
        int rows_number = source_mat.rows;
        for (int src_row = 0; src_row < rows_number - limit; src_row++)
        {
            for (int src_col = 0; src_col < cols_number - limit; src_col++)
            {
                for (int ch = 0; ch < channels_number; ch++)
                {
                    for (int flt_row = 0; flt_row < size; flt_row++)
                    {
                        for (int flt_col = 0; flt_col < size; flt_col++)
                        {

                            if (type == "Gaussian")
                            {
                                pixel_value += source_mat.at<cv::Vec3b>(src_row + flt_row, src_col + flt_col)[ch] * filter[flt_row][flt_col];
                            }
                            else if (type == "Mean" || type == "Median")
                            {
                                sub_matrix.push_back(source_mat.at<cv::Vec3b>(src_row + flt_row, src_col + flt_col)[ch]);
                            }
                        }
                    }

                    if (type == "Gaussian")
                    {
                        source_mat.at<cv::Vec3b>(src_row, src_col)[ch] = (uchar)pixel_value;
                        pixel_value = 0;
                    }
                    else if (type == "Mean")
                    {
                        source_mat.at<cv::Vec3b>(src_row, src_col)[ch] = sub_matrix.mean();
                        sub_matrix.clear();
                    }
                    else if (type == "Median")
                    {
                        source_mat.at<cv::Vec3b>(src_row, src_col)[ch] = sub_matrix.median();
                        sub_matrix.clear();
                    }
                }
            }
        }
        return Image(source_mat.colRange(0, cols_number - limit).rowRange(0, rows_number - limit));
    }

    Image convert(const Image &img, std::string from, std::string to)
    {
        Image dest;

        if (from == "bgr" && to == "gray")
        {
            cvector<Image> splt = split(img);
            cv::Mat cp = img.mat.clone();
            cv::Mat grayscaled_image = cv::Mat(cp.rows, cp.cols, CV_8UC1);
            double gray = 0;
            for (int i = 0; i < splt[0].mat.rows; i++)
            {
                for (int j = 0; j < splt[0].mat.cols; j++)

                {
                    gray = (0.299 * cp.at<cv::Vec3b>(i, j)[2]) + (0.587 * cp.at<cv::Vec3b>(i, j)[1]) + (0.114 * cp.at<cv::Vec3b>(i, j)[0]);
                    grayscaled_image.at<uchar>(i, j) = gray;
                }
            }
            dest = Image(grayscaled_image);
            /*
            std::cout<<cp.mat.type()<<std::endl;

           cv::Mat cpy = img.mat.clone();
            cvtColor(img.mat,cpy,cv::COLOR_BGR2GRAY);
                dest  = Image(cpy);
                */
        }
        else if (from == "bgr" && to == "hsv")
        {
            float fH, fS, fV;
            cvector<Image> splt = split(img);
            Image cp = img.mat.clone();
            for (int i = 0; i < splt[0].mat.rows; i++)
            {
                for (int j = 0; j < splt[0].mat.cols; j++)

                {
                    fH = 0;
                    fS = 0;
                    fV = 0;
                    RGBtoHSV((float)(img.mat.at<cv::Vec3b>(i, j)[2]), (float)(img.mat.at<cv::Vec3b>(i, j)[1]), (float)(img.mat.at<cv::Vec3b>(i, j)[0]), &fH, &fS, &fV);

                    cp.mat.at<cv::Vec3b>(i, j)[0] = round(fH / 10);
                    cp.mat.at<cv::Vec3b>(i, j)[1] = fS;
                    cp.mat.at<cv::Vec3b>(i, j)[2] = fV;
                }
            }
            // std::cout<<"img  "<<(int)img.mat.at<cv::Vec3b>(10,10)[2]<<" "<<(int)img.mat.at<cv::Vec3b>(10,10)[1]<<" "<<(int)img.mat.at<cv::Vec3b>(10,10)[0]<<std::endl;
            // std::cout<<"cp  "<<(int)cp.mat.at<cv::Vec3b>(10,10)[0]<<" "<<(int)cp.mat.at<cv::Vec3b>(10,10)[1]<<" "<<(int)cp.mat.at<cv::Vec3b>(10,10)[2]<<std::endl;
            dest = cp;
            // std::cout<<"dest  "<<(int)dest.mat.at<cv::Vec3b>(10,10)[0]<<" "<<(int)dest.mat.at<cv::Vec3b>(10,10)[1]<<" "<<(int)dest.mat.at<cv::Vec3b>(10,10)[2]<<std::endl;
        }

        else if (from == "hsv" && to == "bgr")
        {
            float fR, fG, fB;
            cvector<Image> splt = split(img);
            Image cp = img.mat.clone();
            for (int i = 0; i < splt[0].mat.rows; i++)
            {
                for (int j = 0; j < splt[0].mat.cols; j++)
                {
                    fR = 0;
                    fG = 0;
                    fB = 0;
                    HSVtoRGB(&fR, &fG, &fB, (float)(img.mat.at<cv::Vec3b>(i, j)[0]) * 10, (float)((img.mat.at<cv::Vec3b>(i, j)[1]) / 100.0), (float)((img.mat.at<cv::Vec3b>(i, j)[2]) / 100.0));
                    cp.mat.at<cv::Vec3b>(i, j)[0] = fB * 255;
                    cp.mat.at<cv::Vec3b>(i, j)[1] = fG * 255;
                    cp.mat.at<cv::Vec3b>(i, j)[2] = fR * 255;
                }
            }
            dest = cp;
            //         std::cout<<"img  "<<(int)img.mat.at<cv::Vec3b>(10,10)[0]<<" "<<(float)((img.mat.at<cv::Vec3b>(10,10)[1])/100.0)<<" "<<(float)((img.mat.at<cv::Vec3b>(10,10)[2])/100.0)<<std::endl;
            // std::cout<<"cp  "<<(int)cp.mat.at<cv::Vec3b>(10,10)[2]<<" "<<(int)cp.mat.at<cv::Vec3b>(10,10)[1]<<" "<<(int)cp.mat.at<cv::Vec3b>(10,10)[0]<<std::endl;
            // std::cout<<"dest  "<<(int)dest.mat.at<cv::Vec3b>(10,10)[2]<<" "<<(int)dest.mat.at<cv::Vec3b>(10,10)[1]<<" "<<(int)dest.mat.at<cv::Vec3b>(10,10)[0]<<std::endl;
        }
        else
        {
            throw "Invalid conversion";
        }
        return dest;
    }

    cvector<Image> split(const Image &img)
    {
        cv::Mat channels[3];
        split(img.mat, channels);
        cvector<Image> imgs = {channels[0], channels[1], channels[2]};
        return imgs;
    }

    cvector<double> sobel(const Image &img, bool dx, bool dy)
    {
        if (!dx && !dy)
        {
            throw "Must set dx or dy or both";
        }
        cvector<cvector<double>> x = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1},
        };
        cvector<cvector<double>> y = {
            {1, 2, 1},
            {0, 0, 0},
            {-1, -2, -1},
        };

        size_t dim = (img.mat.rows - 3 + 1) * (img.mat.cols - 3 + 1);
        cvector<double> gx(dim, 0);
        cvector<double> gy(dim, 0);
        if (dx)
        {
            gx = filter(img, x);
        }
        if (dy)
        {
            gy = filter(img, y);
        }
        return cvector<double>::mag(gx, gy);
    }
    cvector<uchar> scale(cvector<double> pixels)
    {
        pixels = pixels.abs();
        cvector<uchar> res;
        double scaled = (255.0 / pixels.max());
        for (auto itr = pixels.begin(); itr != pixels.end(); itr++)
        {
            res.push_back((uchar)std::round((*itr) * scaled));
        }
        return res;
    }
    cvector<double> filter(const Image &img, cvector<cvector<double>> mask)
    {
        int img_rows = img.mat.rows;
        int img_cols = img.mat.cols;
        int mask_rows = mask.size();
        int mask_cols = mask[0].size();

        // convert uchar to int to handle -ve values
        cvector<double> fltr(img.pixels.begin(), img.pixels.end());
        cvector<cvector<double>> mtrx = fltr.to_2d(img_rows, img_cols);
        fltr.clear();

        for (int row = 0; row < (img_rows - mask_rows + 1); row++)
        {
            for (int col = 0; col < (img_cols - mask_cols + 1); col++)
            {
                cvector<cvector<double>> sub = mtrx.range(row, row + mask_rows, col, col + mask_cols);
                double px = 0;
                for (int mask_row = 0; mask_row < mask_rows; mask_row++)
                {
                    px += sub[mask_row].dot(mask[mask_row]);
                }
                fltr.push_back(px);
            }
        }
        return fltr;
    }



}
