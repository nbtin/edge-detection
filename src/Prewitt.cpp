#include "Prewitt.h"
#include <vector>

// detect edges by prewitt algorithm
int detectByPrewitt(Mat src, Mat& dst, int dx, int dy)
{
    Mat inputImage;
    cvtColor(src, inputImage, COLOR_BGR2GRAY);

    if (inputImage.empty())
    {
        cout << "Error: Could not read input image" << endl;
        return -1;
    }

    Mat outputImage(inputImage.size(), CV_8UC1);

    int prewittX[3][3] = { {-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1} };
    int prewittY[3][3] = { {-1, -1, -1}, {0, 0, 0}, {1, 1, 1} };


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
                        Gx += inputImage.at<uchar>(i + k, j + l) * prewittX[-k + 1][-l + 1];
                    if (dy == 1)
                        Gy += inputImage.at<uchar>(i + k, j + l) * prewittY[-k + 1][-l + 1];

                }
            }

            uchar G = saturate_cast<uchar>(saturate_cast<uint>(Gx) + saturate_cast<uint>(Gy));
            outputImage.at<uchar>(i, j) = G;
        }
    }

    dst = outputImage;
    return 0;
}

// detect edges by using filter2D function with prewitt kernel
void detectByPrewittOpenCV(Mat src, Mat& dst, int dx, int dy) {
    Mat prewittFilterX = (Mat_<float>(3, 3) <<
        1, 0, -1,
        1, 0, -1,
        1, 0, -1);

    Mat prewittFilterY = (Mat_<float>(3, 3) <<
        1, 1, 1,
        0, 0, 0,
        -1, -1, -1);
    
    if (src.channels() != 1)
        cvtColor(src, src, COLOR_BGR2GRAY);
   
    Mat resX = Mat::zeros(Size(src.rows, src.cols), CV_8UC1);
    Mat resY = Mat::zeros(Size(src.rows, src.cols), CV_8UC1);


    if (dx == 1)
        filter2D(src, resX, CV_8UC1, prewittFilterX);
    if (dy == 1)
        filter2D(src, resY, CV_8UC1, prewittFilterY);
    dst = abs(resX) + abs(resY);
}