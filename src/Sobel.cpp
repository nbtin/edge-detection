#include "Sobel.h"
#include <vector>

// detect edges by using sobel kernels
int detectBySobel(Mat src, Mat& dst, int dx, int dy)
{
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

    Mat outputImage(inputImage.size(), CV_8UC1);

    int sobelX[3][3] = { {1, 0, -1}, {2, 0, -2}, {1, 0, -1} };
    int sobelY[3][3] = { {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} };


    for (int i = 1; i < inputImage.rows - 1; ++i)
    {
        for (int j = 1; j < inputImage.cols - 1; ++j)
        {
            int Gx = 0, Gy = 0;

            for (int k = -1; k <= 1; ++k)
            {
                for (int l = -1; l <= 1; ++l)
                {
                    if (dx == 1)
                        Gx += inputImage.at<uchar>(i + k, j + l) * sobelX[-k + 1][-l + 1];
                    if (dy == 1)
                        Gy += inputImage.at<uchar>(i + k, j + l) * sobelY[-k + 1][-l + 1];

                }
            }
            

            uchar G = saturate_cast<uchar>(saturate_cast<uint>(Gx) + saturate_cast<uint>(Gy));

            outputImage.at<uchar>(i, j) = G;
        }
    }

    dst = outputImage;
    return 0;
}