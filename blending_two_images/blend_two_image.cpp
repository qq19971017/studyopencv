#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(void) {
	double alpha = 0.5;
	double beta, input;
	Mat src1, src2, dst;
	cout << "Simple Linear Blender" << endl;
	cout << "*Enter alpha [0.0-1.0]" << endl;
	cin >> input;

	if (input >= 0.0&&input <= 1.0)
		alpha = input;
	src1 = imread("data/LinuxLogo.jpg");
	src2 = imread("data/WindowsLogo.jpg");
	if (src1.empty()) { cout << "Error loading src1" << endl; return -1; }
	if (src2.empty()) { cout << "Error loading src2" << endl; return -1; }

	beta = (1.0 - alpha);
	addWeighted(src1, alpha, src2, beta,0.0,dst);
	imshow("Linear Blend", dst);
	waitKey(0);

	return 0;
}
