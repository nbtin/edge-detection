#pragma once
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

Mat readImage(string fileName) {
	return imread(fileName);
}

//show image windows before and after
void showResults(Mat src, Mat res, string nameSrc, string nameRes, bool showSrc = true, bool showRes = true) {
    if (showSrc) {
        namedWindow(nameSrc, WINDOW_AUTOSIZE);
        imshow(nameSrc, src);
    }

    if (showRes) {
        namedWindow(nameRes, WINDOW_AUTOSIZE);
        imshow(nameRes, res);
    }

    //waitKey(0);
}

// detect with 2 versions of sobel
void SobelDetect(string fileName, int dx, int dy) {
	Mat input = readImage(fileName);
	Mat output;
	Mat outputOpenCV;

	int res = detectBySobel(input, output, dx, dy);

	Mat inputOpenCV;
	cvtColor(input, inputOpenCV, COLOR_BGR2GRAY);
	Sobel(inputOpenCV, outputOpenCV, CV_8UC1, dx, dy);

	if (res == 0) {
		showResults(input, output, "Original", "Sobel", 1, 1);
	}
	showResults(input, outputOpenCV, "Original", "Sobel OpenCV", 0, 1);
	waitKey(0);
}

// detect with prewitt
void PrewittDetect(string fileName, int dx, int dy) {
	Mat input = readImage(fileName);
	Mat output;
	//Mat outFilter2D;

	int res = detectByPrewitt(input, output, dx, dy);

	//detectByPrewittOpenCV(input, outFilter2D, dx, dy);

	if (res == 0) {
		showResults(input, output, "Original", "Prewitt", 1, 1);
	}

	//showResults(input, outFilter2D, "Original", "Prewitt Filter2D (OpenCV)", 0, 1);
	waitKey(0);
}

// detect with 2 versions of Canny
void CannyDetect(string fileName, int lower, int upper) {
	Mat input = readImage(fileName);
	Mat output;
	Mat outputOpenCV;

	int res = detectByCanny(input, output, lower, upper);


	Mat inputOpenCV;
	cvtColor(input, inputOpenCV, COLOR_BGR2GRAY);
	Canny(inputOpenCV, outputOpenCV, 100, 200);

	if (res == 0) {
		showResults(input, output, "Original", "Canny", 1, 1);
	}
	showResults(input, outputOpenCV, "Original", "Canny OpenCV", 0, 1);

	waitKey(0);
}

// Detect with 2 versions of Laplace
void LaplaceDetect(string fileName, double threshold = 20) {
	Mat input = readImage(fileName);
	Mat output;
	// Mat output2;
	Mat outputOpenCV;

	int res = detectByLaplace(input, output, threshold);
	// int res2 = detectByLaplaceNoZeroCrossing(input, output2);


	Mat inputOpenCV;
	cvtColor(input, inputOpenCV, COLOR_BGR2GRAY);
	Laplacian(inputOpenCV, outputOpenCV, CV_8UC1);

	if (res == 0) {
		showResults(input, output, "Original", "Laplace", 1, 1);
	}
	// if (res2 == 0) {
	// 	showResults(input, output2, "Original", "Laplace No zero-crossing", 0, 1);
	// }
	showResults(input, outputOpenCV, "Original", "Laplace OpenCV", 0, 1);

	waitKey(0);
}