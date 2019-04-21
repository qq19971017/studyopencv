#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
	char *imageName = argv[1];
	Mat image;
	image = imread(imageName, IMREAD_COLOR);
	
	//empty image
	//data means pointer to the data of image
	if (argc != 2 || !image.data) {
		cout << "image is empty";
		return -1;
	}

	Mat gray_image;

	//RGB image converts gray image
	cvtColor(image, gray_image, COLOR_BGR2GRAY);
	imwrite("image_gray.jpg", gray_image);

	//@para WINDOW_AUTOSIZE:the user can't resize the image
	//@para WINDOW_FREERATIO: the image can expent an much as it can
	namedWindow(imageName,WINDOW_AUTOSIZE);
	namedWindow("grayimage", WINDOW_FREERATIO);

	imshow(imageName, image);
	imshow("grayimage", gray_image);
	waitKey(0);
	return 0;
}