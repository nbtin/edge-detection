#pragma once
#include "Sobel.h"
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int detectByCanny(Mat src, Mat& dst, int lower, int upper);