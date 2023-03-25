#include <opencv2/opencv.hpp>
#include "active_contour.h"
#include <QDebug>
#include <iostream>
#include <vector>

using namespace std;


void circle_contour(cv::Point center, double radius, int numberOfPoints, int *x_coordinates, int *y_coordinates)
{
    // Compute the angular resolution of the contour
    double resolution = 2 * CV_PI / numberOfPoints;

    // Generate the contour points
    for (int i = 0; i < numberOfPoints; i++)
    {
        // Compute the angle of the current contour point
        double angle = i * resolution;

        // Compute the x and y coordinates of the current contour point
        double x = center.x + radius * std::cos(angle);
        double y = center.y - radius * std::sin(angle);

        // Store the coordinates in the output arrays
        x_coordinates[i] = (int)std::round(x);
        y_coordinates[i] = (int)std::round(y);
    }
}
void draw_contour(cv::Mat Image, int numberOfPoints, int *x_coordinates, int *y_coordinates)
{
    int next;
    for (int i = 0; i < numberOfPoints; i++)
    {
        next = (i + 1) % numberOfPoints;
        line(Image, cv::Point(y_coordinates[i], x_coordinates[i]), cv::Point(y_coordinates[next], x_coordinates[next]), cv::Scalar(255, 0, 0), 2);
    }
}

double contour_area(int numberOfPoints, int *x_cooridinates, int *y_cooridinates)
{
    double area = 0.0;
    // Calculate value of shoelace formula => 1/2 [ (x1y2 + x2y3 + … + xn-1yn + xny1) – (x2y1 + x3y2 + … + xnyn-1 + x1yn) ]
    int j = numberOfPoints - 1;
    for (int i = 0; i < numberOfPoints; i++)
    {
        area += (x_cooridinates[j] + x_cooridinates[i]) * (y_cooridinates[j] - y_cooridinates[i]);
        j = i; // j is previous vertex to i
    }
    return std::abs(area / 2.0);
}

double contour_perimeter(int *x_points, int *y_points, int points_n)
{
    double distance_sum = 0;
    for (int i = 0; i < points_n; i++)
    {
        int next_point = i + 1;
        if (i == points_n - 1)
        {
            next_point = 0;
        }

        double distance = points_distance(x_points[i], y_points[i], x_points[next_point], y_points[next_point]);
        distance_sum += distance;
    }
    return distance_sum;
}

double internal_energy(int *x_points, int *y_points, int points_n, double alpha, double beta)
{
    double curv_sum = 0;
    double cont_sum = 0;
    double avg_dist = contour_perimeter(x_points, y_points, points_n) / points_n;

    // Compute the average angle between adjacent line segments
    double avg_angle = 0;
    for (int i = 0; i < points_n; i++) {
        int next_point = (i + 1) % points_n;
        double dx = x_points[next_point] - x_points[i];
        double dy = y_points[next_point] - y_points[i];
        double angle = std::atan2(dy, dx);
        if (angle < 0) angle += 2 * CV_PI;
        avg_angle += angle;
    }
    avg_angle /= points_n;

    // Compute the energy due to contour smoothness and curvature
    for (int i = 0; i < points_n; i++)
    {
        int next_point = (i + 1) % points_n;
        int prev_point = (i + points_n - 1) % points_n;

        // Compute the distance between adjacent contour points
        double dist = points_distance(x_points[i], y_points[i], x_points[next_point], y_points[next_point]);

        // Compute the deviation from the desired distance
        double cont_dev = dist - avg_dist;
        cont_sum += cont_dev * cont_dev;

        // Compute the angle deviation between adjacent line segments
        double dx1 = x_points[i] - x_points[prev_point];
        double dy1 = y_points[i] - y_points[prev_point];
        double dx2 = x_points[next_point] - x_points[i];
        double dy2 = y_points[next_point] - y_points[i];
        double angle1 = std::atan2(dy1, dx1);
        double angle2 = std::atan2(dy2, dx2);
        if (angle1 < 0) angle1 += 2 * CV_PI;
        if (angle2 < 0) angle2 += 2 * CV_PI;
        double angle_dev = std::abs(angle1 - angle2);
        if (angle_dev > CV_PI) angle_dev = 2 * CV_PI - angle_dev;
        curv_sum += angle_dev * angle_dev;
    }

    double energy = alpha * cont_sum + beta * curv_sum;
    return energy;}

img::Image external_energy(img::Image source)
{
    img::Image filtered_Gaussian = img::noise_filter(source, 3, "Gaussian");
    img::Image gray = img::convert(filtered_Gaussian, "bgr", "gray");
    cv::Canny(gray.mat, gray.mat, 0, 255);
    return img::Image(gray);

}


cv::Mat greedy_contour(img::Image source, int iterations, float alpha, float beta, float gamma, int* x_points, int* y_points, int points_n, int window_size, bool plot) {
    img::Image sobel_energy = external_energy(source);
    cvector<cvector<int>> window = window_neighbours(window_size);
    int current_x[180];
    int current_y[180];

    cv::Mat plot_img;
    int point_energy;
    int min_energy;
    int min_index;
    int movements = 0;
    int iteration = 0;
    bool loob = true;
    int threshold = 5;
    int neighbours_size = pow(window_size, 2);

    while (loob) {
        movements = 0;

        for (int i = 0; i < points_n; i++) {
            min_energy = INT_MAX;

            for (int j = 0; j < neighbours_size; j++) {
                current_x[i] = x_points[i] + window[j][0];
                current_y[i] = y_points[i] + window[j][1];

                if (current_x[i] < sobel_energy.mat.rows && current_x[i] > 0 && current_y[i] > 0 && current_y[i] < sobel_energy.mat.cols) {
                    point_energy = sobel_energy.mat.at<uchar>(current_x[i], current_y[i]) * -1 * gamma + internal_energy(current_x, current_y, points_n, alpha, beta);

                    if (point_energy < min_energy) {
                        min_energy = point_energy;
                        min_index = j;
                    }
                }
            }

            if (min_energy < INT_MAX) {
                x_points[i] = x_points[i] + window[min_index][0];
                y_points[i] = y_points[i] + window[min_index][1];

                if (window[min_index][0] != 0 || window[min_index][1] != 0) {
                    movements++;
                }
            }
        }

        iteration++;

        if (plot == true) {
            plot_img = source.mat.clone();
            draw_contour(plot_img, points_n, x_points, y_points);
        }

        if (iteration > iterations || movements < threshold) {
            loob = false;
        }
    }

    return plot_img;
}


//cv::Mat greedy_contour(img::Image source, int iterations, float alpha, float beta, float gamma, int* x_points, int* y_points, int points_n, int window_size, bool plot) {
//    img::Image sobel_energy = external_energy(source);
//    cvector<cvector<int>> window = window_neighbours(window_size);
//    int current_x[180];
//    int current_y[180];



//    cv::Mat plot_img;
//    int point_energy;
//    int min_energy;
//    int min_index;
//    int movements = 0;
//    int iteration = 0;
//    bool loob = true;
//    int threshold = 5;
//    int neighbours_size = pow(window_size, 2);

//    while (loob) {
//        movements = 0; // Reset movements counter for each iteration

//        for (int i = 0; i < points_n; i++) {
//            min_energy = INT_MAX; // Initialize min_energy to a large value

//            for (int j = 0; j < neighbours_size; j++) {
//                current_x[i] = x_points[i] + window[j][0];
//                current_y[i] = y_points[i] + window[j][1];



//                if (current_x[i] < sobel_energy.mat.rows && current_x[i] > 0 && current_y[i] > 0 && current_y[i] < sobel_energy.mat.cols) {
//                    point_energy = sobel_energy.mat.at<uchar>(current_x[i], current_y[i]) * -1 * gamma + internal_energy(current_x, current_y, points_n, alpha, beta);

//                    if (point_energy < min_energy) {
//                        min_energy = point_energy;
//                        min_index = j;
//                    }
//                }
//            }

//            // Update the contour point if a better point was found
//            if (min_energy < INT_MAX) {
//                x_points[i] = x_points[i] + window[min_index][0];
//                y_points[i] = y_points[i] + window[min_index][1];

//                if (window[min_index][0] != 0 || window[min_index][1] != 0) {
//                    movements++;
//                }
//            }
//        }

//        iteration++;

//        if (plot == true) {
//            plot_img = source.mat.clone();
//            draw_contour(plot_img, points_n, x_points, y_points);
//        }

//        if (iteration > iterations || movements < threshold) {
//            loob = false;
//            vector<int> chainCode;
//            for (int i = 0; i < points_n - 1; i++)
//            {
//                int dx = x_points[i + 1] - x_points[i];
//                int dy = y_points[i + 1] - y_points[i];

//                double slope = (double)dy / (double)dx;
//                double angle = atan(slope);
//                angle = abs(angle * 180 / 3.14);

//                // Calculate the quadrant
//                int quadrant;
//                if (dx > 0 && dy >= 0) {
//                    quadrant = 1;
//                }
//                else if (dx <= 0 && dy > 0) {
//                    quadrant = 2;
//                    angle = 180 - angle;
//                }
//                else if (dx < 0 && dy <= 0) {
//                    quadrant = 3;
//                    angle = 180 + angle;

//                }
//                else if (dx >= 0 && dy < 0) {
//                    quadrant = 4;
//                    angle = 360 - angle;
//                }
//                cout << angle << endl;
//                // Calculate the chaincode for the quadrant
//                int code;
//                if (angle >= 337.5 || angle < 22.5) {
//                    code = 0;
//                }
//                else if (angle >= 22.5 && angle < 67.5) {
//                    code = 1;
//                }
//                else if (angle >= 67.5 && angle < 112.5) {
//                    code = 2;
//                }
//                else if (angle >= 112.5 && angle < 157.5) {
//                    code = 3;
//                }
//                else if (angle >= 157.5 && angle < 202.5) {
//                    code = 4;
//                }
//                else if (angle >= 202.5 && angle < 247.5) {
//                    code = 5;
//                }
//                else if (angle >= 247.5 && angle < 292.5) {
//                    code = 6;
//                }
//                else if (angle >= 292.5 && angle < 337.5) {
//                    code = 7;
//                }
//                // Add the chaincode to the sequence
//                chainCode.push_back(code);
//            }
//        }
//    }
//    return plot_img;
//}


cvector<cvector<int>> window_neighbours(int size)
{
    cvector<cvector<int>> window;
    cvector<int> point;

    for (int i = -size / 2; i <= size / 2; i++)
    {

        for (int j = -size / 2; j <= size / 2; j++)
        {
            point = {i, j};
            window.push_back(point);
        }
    }
    return window;
}



std::vector<std::pair<int, int>> chain_code(std::vector<int> x, std::vector<int> y) {
    int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    std::vector<std::pair<int, int>> code;
    for (int i = 1; i < (int)x.size(); i++) {
        // Determine the direction of movement
        int dxn = x[i] - x[i-1];
        int dyn = y[i] - y[i-1];
        int direction = -1;
        for (int j = 0; j < 8; j++) {
            if (dx[j] == dxn && dy[j] == dyn) {
                direction = j;
                break;
            }
        }
        code.push_back(std::make_pair(dx[direction], dy[direction]));
    }
    return code;
}


cv::Mat active_contour(cv::Mat mat,int iterations, float alpha, float beta, float gamma, int points, int radius){
    // Create a new matrix with the same size as the source matrix
    cv::Mat dst(mat.size(), mat.type());
    img::Image original_image = img::Image(mat);
    cv::Size sz = original_image.mat.size();
    int x_cooridinates[80];
    int y_cooridinates[80];
    circle_contour(cv::Point(sz.width / 2, sz.height / 2), radius, points, x_cooridinates, y_cooridinates);
    dst = greedy_contour(original_image, iterations, alpha, beta, gamma, x_cooridinates, y_cooridinates, points, 11, true);
    cv::resize(dst, dst, cv::Size(360, round(360*dst.rows/dst.cols)));
    return dst;
}





