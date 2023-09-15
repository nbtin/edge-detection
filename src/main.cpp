#include "Sobel.h"
#include "Prewitt.h"
#include "Canny.h"
#include "Laplace.h"
#include "utils.h"

int main(int argc, char** argv)
{
    string operation;
    string imagePath;
    if (argc > 2){
        imagePath = argv[1];
        operation = argv[2];
        transform(operation.begin(), operation.end(), operation.begin(), ::tolower);
    }
    

    // laplace
    if (argc == 4 && operation == "laplace") {
        LaplaceDetect(imagePath, atoi(argv[3]));
        return 0;
    }

    // others
    if (argc == 5) {
        int dx = atoi(argv[3]);
        int dy = atoi(argv[4]);
        cout << "dx = " << dx << "\ndy = " << dy << endl;
        if (operation == "sobel") {
            SobelDetect(imagePath, dx, dy);
            return 0;
        }
        if (operation == "prewitt") {
            PrewittDetect(imagePath, dx, dy);
            return 0;
        }
        if (operation == "canny") {
            CannyDetect(imagePath, dx, dy);
            return 0;
        }
    }

    // user guide
    if (argc == 2 && strcmp(argv[1], "help") == 0) {
        cout << "Usage: " << argv[0] << " <image_path> <operation> [<param>]\n" << endl;
        cout << " - <image_path>: path of the input image.\n\n";
        cout << " - <operation>: sobel, prewitt, canny, laplace.\n\n";
        cout << " - [<param>]:\n\t + Sobel: dx, dy - set each value equal to 1 to specify the orientation of detection, and 0 otherwise.\n\t\t\t\t(dx for vertical, dy for horizontal).";
        cout << "\n\t + Prewitt: dx, dy - set each value equal to 1 to specify the orientation of detection, and 0 otherwise.\n\t\t\t\t(dx for vertical, dy for horizontal).";
        cout << "\n\t + Canny: lower, upper - specify lower and upper threshold for the Canny edge detection.\n\t\t\t\tThese thresholds are in [0, 255]\n\t\t\t\t(Canny recommended a upper:lower ratio between 2:1 and 3:1).";
        cout << "\n\t + Laplace: threshold - specify the sensitivity in determining which pixel is probably an edge.\n";
    }
    
    return -1;
}