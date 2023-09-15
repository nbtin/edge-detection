#pragma once
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int detectByPrewitt(Mat src, Mat& dst, int dx, int dy);
void detectByPrewittOpenCV(Mat src, Mat& dst, int dx, int dy);