#pragma once
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int detectByLaplace(Mat src, Mat& dst, double threshold);
int detectByLaplaceNoZeroCrossing(Mat src, Mat& dst);