#include "Laplace.h"


// detect edges by laplace
int detectByLaplace(Mat src, Mat& dst, double threshold) {
    // Convert to grayscale
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
    
    GaussianBlur(inputImage, inputImage, Size(5, 5), 0);

    int laplace1[3][3] = { {0, 1, 0}, {1, -4, 1}, {0, 1, 0} };
    int laplace2[3][3] = { {1, 4, 1}, {4, -20, 4}, {1, 4, 1} };
    int laplace3[3][3] = { {-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1} };


    // Apply Laplace filter
    Mat laplacian(inputImage.size(), CV_32F, Scalar(0));
    for (int i = 1; i < inputImage.rows - 1; i++) {
        for (int j = 1; j < inputImage.cols - 1; j++) {
            for (int k = -1; k < 2; k++) {
                for (int h = -1; h < 2; h++) {
                    int pixel = inputImage.at<uchar>(i + k, j + h);
                    laplacian.at<float>(i, j) += pixel * laplace3[-k + 1][-h + 1];
                }
            }

        }
    }

    // Find zero crossings
    Mat edges(inputImage.size(), CV_8UC1, Scalar(0));
    for (int i = 1; i < laplacian.rows - 1; i++) {
        for (int j = 1; j < laplacian.cols - 1; j++) {
            float center = laplacian.at<float>(i, j);
            float north = laplacian.at<float>(i - 1, j);
            float south = laplacian.at<float>(i + 1, j);
            float east = laplacian.at<float>(i, j + 1);
            float west = laplacian.at<float>(i, j - 1);
            if ((center * north < 0) || (center * south < 0) || (center * east < 0) || (center * west < 0))
            {
                if (abs(center - north) > threshold || abs(center - south) > threshold || abs(center - east) > threshold || abs(center - west) > threshold)
                {
                    edges.at<uchar>(i, j) = 255;
                }
            }
        }
    }

    dst = edges;

    return 0;
}

// detect edges with laplace but without zero crossing
int detectByLaplaceNoZeroCrossing(Mat src, Mat& dst) {
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

    GaussianBlur(inputImage, inputImage, Size(3, 3), 0);

    int laplace1[3][3] = { {0, 1, 0}, {1, -4, 1}, {0, 1, 0} };
    int laplace2[3][3] = { {1, 4, 1}, {4, -20, 4}, {1, 4, 1} };
    int laplace3[3][3] = { {-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1} };


    // Apply Laplace filter
    Mat edges(inputImage.size(), CV_8UC1, Scalar(0));
    Mat laplacian(inputImage.size(), CV_32F, Scalar(0));
    for (int i = 1; i < inputImage.rows - 1; i++) {
        for (int j = 1; j < inputImage.cols - 1; j++) {
            float sum = 0;
            for (int k = -1; k < 2; k++) {
                for (int h = -1; h < 2; h++) {
                    sum += inputImage.at<uchar>(i + k, j + h) * laplace3[-k + 1][-h + 1];
                    //laplacian.at<float>(i, j) += inputImage.at<uchar>(i + k, j + h) * laplace2[-k + 1][-h + 1];
                }
            }
            edges.at<uchar>(i, j) = saturate_cast<uchar>(sum);

        }
    }

    dst = edges;

    return 0;
}
