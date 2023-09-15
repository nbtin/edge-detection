#include "Canny.h"

int detectByCanny(Mat src, Mat& dst, int lower, int upper) {
	/*
	B1: Convert input to grayscale image.
	B2: Filter noise using Gaussian blur.
	B3: Get the derivative Gx and Gy by Sobel operator.
	B4: Calculate the angle (arctan) of every pixel and round it to 0, 45, 90 or 135.
	B5: Non-max suppression.
	B6: Apply Hysteresis. (upper and lower threshold).
	*/
    // B1
    Mat inputImage;
    if (src.channels() != 1)
        cvtColor(src, inputImage, COLOR_BGR2GRAY);
    else
        inputImage = src;
    
    if (inputImage.empty())
    {
        cout << "Error: Could not read input image" << endl;
        return -1;
    }
    
    // B2
    GaussianBlur(inputImage, inputImage, Size(3, 3), 0);


    Mat outputImage(inputImage.size(), CV_8UC1);
    Mat orientation = Mat::zeros(inputImage.size(), CV_32FC1);

    int sobelX[3][3] = { {1, 0, -1}, {2, 0, -2}, {1, 0, -1} };
    int sobelY[3][3] = { {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} };

    // B3 + B4
    Mat magnitude = Mat::zeros(inputImage.size(), CV_32FC1);

    for (int i = 1; i < inputImage.rows - 1; ++i)
    {
        for (int j = 1; j < inputImage.cols - 1; ++j)
        {
            int Gx = 0, Gy = 0;

            for (int k = -1; k <= 1; ++k)
            {
                for (int l = -1; l <= 1; ++l)
                {
                    Gx += inputImage.at<uchar>(i + k, j + l) * sobelX[-k + 1][-l + 1];
                    Gy += inputImage.at<uchar>(i + k, j + l) * sobelY[-k + 1][-l + 1];

                }
            }

            double G = sqrt(Gx * Gx + Gy * Gy);
            magnitude.at<float>(i, j) = G;

            float angle = atan2(Gy, Gx) * 180 / CV_PI;
            angle = round(angle / 45.0) * 45.0;

            // Map angles -> 0, 45, 90, 135
            if (angle < 0) angle += 180;
            if (angle >= 180.0) angle -= 180.0;
            //cout << angle << endl;
            orientation.at<float>(i, j) = angle;
            
        }
    }

    // B5
    Mat nonMax = Mat::zeros(inputImage.size(), CV_32FC1);
    for (int i = 1; i < magnitude.rows - 1; i++) {
        for (int j = 1; j < magnitude.cols - 1; j++) {
            // Compute neighbor indices
            int x1 = i - 1, x2 = i + 1;
            int y1 = j - 1, y2 = j + 1;
            // Get gradient angle
            double angle_deg = orientation.at<float>(i, j);
            // Check angle and get neighboring magnitudenitudes
            double magnitude1, magnitude2;
            if (angle_deg == 0) {  // horizontal edge
                magnitude1 = magnitude.at<float>(i, y1);
                magnitude2 = magnitude.at<float>(i, y2);
            }
            else if (angle_deg == 135) {  // diagonal edge (top-right to bottom-left)
                magnitude1 = magnitude.at<float>(x1, y2);
                magnitude2 = magnitude.at<float>(x2, y1);
            }
            else if (angle_deg == 90) {  // vertical edge
                magnitude1 = magnitude.at<float>(x1, j);
                magnitude2 = magnitude.at<float>(x2, j);
            }
            else if (angle_deg == 45) {  // diagonal edge (top-left to bottom-right)
                magnitude1 = magnitude.at<float>(x1, y1);
                magnitude2 = magnitude.at<float>(x2, y2);
            }
            else {
                continue;  // ignore non-cardinal directions
            }
            // Suppress edge if magnitudenitude is not a local maximum along the gradient direction
            double mag = magnitude.at<float>(i, j);
            if (mag > magnitude1 && mag > magnitude2) {
                nonMax.at<float>(i, j) = mag;  // suppress the edge
            }
        }
    }


    // B6
    for (int i = 1; i < inputImage.rows - 1; i++) {
        for (int j = 1; j < inputImage.cols - 1; j++) {
            if (nonMax.at<float>(i, j) > upper) {
                outputImage.at<uchar>(i, j) = 255;
            }
            else if (nonMax.at<float>(i, j) < lower) {
                outputImage.at<uchar>(i, j) = 0;
            }
            else {
                bool hasStrongNeighbor = false;
                for (int k = -1; k <= 1; k++) {
                    for (int h = -1; h <= 1; h++) {
                        if (nonMax.at<float>(i + k, j + h) > upper) {
                            hasStrongNeighbor = true;
                            break;
                        }
                    }
                }
                if (hasStrongNeighbor) {
                    outputImage.at<uchar>(i, j) = 255;
                }
            }
        }
    }

    dst = outputImage;
    return 0;

}