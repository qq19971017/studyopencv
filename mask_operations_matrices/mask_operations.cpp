#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include<opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<sstream>


using namespace cv;
using namespace std;
void Sharpen(const Mat &myImage, Mat& Result);

int main(int argc, char **argv) {
	//lena.jpg:The classical image of computer vision
	const char *filename = argc >= 2 ? argv[1] : "../data/lena.jpg";
	Mat src, dst0, dst1;
	if (argc >= 3 && !strcmp("G", argv[2])) {
		src = imread(filename, IMREAD_GRAYSCALE);
	}
	else {
		src = imread(filename, IMREAD_COLOR);
	}

	if (src.empty()) {
		cout << "Con't open image [" << filename << "] " << endl;
		return -1;
	}

	namedWindow("Input", WINDOW_AUTOSIZE);
	namedWindow("Output", WINDOW_AUTOSIZE);

	imshow("Input", src);
	double t = (double)getTickCount();

	Sharpen(src, dst0);
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Hand written function time passed in seconds: " << t << endl;

	imshow("Output", dst0);
	waitKey();

	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	t = (double)getTickCount();
	filter2D(src, dst1, src.depth(), kernel);
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Built-in filter2D time passed in seconds:     " << t << endl;
	imshow("Output", dst1);
	waitKey();
	return 0;
}

void Sharpen(const Mat &myImage, Mat& Result) {
	CV_Assert(myImage.depth() == CV_8U);
	const int channels = myImage.channels();
	int rows = myImage.rows;
	int cols = myImage.cols;
	Result.create(myImage.size(), myImage.type());
	for (int i = 1; i < rows - 1; ++i) {
		const uchar *pre = myImage.ptr<uchar>(i - 1);
		const uchar *current = myImage.ptr<uchar>(i);
		const uchar *next = myImage.ptr<uchar>(i + 1);
		
		uchar* output = Result.ptr<uchar>(i);
		for (int j = channels; j < channels*( cols - 1); ++j) {
			*output++ = saturate_cast<uchar>(5 * current[j] - current[j - channels]
				- current[j + channels] - next[j] - pre[j]);
		}

		
		Result.row(0).setTo(Scalar(0)); //return Mat(*this, Range::all(), Range(x, x + 1)); ²»°üÀ¨x+1
		Result.row(rows - 1).setTo(Scalar(0));
		Result.col(0).setTo(Scalar(0));
		Result.col(cols - 1).setTo(Scalar(0));
	}
}