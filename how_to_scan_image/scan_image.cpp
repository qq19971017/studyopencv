#include <iostream>
#include <opencv2/core.hpp>
#include <opencv.hpp>
#include <opencv2/core/core.hpp>
#include <sstream>
#include <string>

using namespace std;
using namespace cv;

Mat& ScanImageAndReduceC(Mat &I, const uchar *table);
Mat& ScanImageAndReduceIterator(Mat &I, const uchar *table);
Mat &ScanImageAndReduceRandomAccess(Mat &I, const uchar *table);

int main(int argc, char **argv) {
	if (argc < 3) {
		cout << "没有足够的参数" << endl;
		return -1;
	}

	Mat I,J;
	//the argv[3] if == G represent that the image id grayscale 
	//strcmp(a,b) is compare ,a==b return 0
	if (argc == 4 && !strcmp(argv[3],"G")) {
		I = imread(argv[1], IMREAD_GRAYSCALE);
	}

	else {
		I = imread(argv[1], IMREAD_COLOR);
	}

	if (I.empty()) {
		cout << "The image"<<argv[1]<<"could not be loaded" << endl;
		return -1;
	}

	//product a look up table
	int dividewith;
	stringstream s;
	s << argv[2];
	s >> dividewith;
	uchar table[256];
	for (int i = 0; i < 256; i++) {
		table[i] = (uchar)(dividewith* (i / dividewith));
	}
	
	const int time = 100;
	double t;
	 t = (double)getTickCount();
	for (int i = 0; i < time; i++) {
		Mat clone_i;
		clone_i = ScanImageAndReduceC(I, table);
	}
	t = ((double)getTickCount() - t) / getTickFrequency() * 1000;
	t /= 100;
	cout << "Time of reducing with the C operator [] (averaged for "
		<< time << " runs): " << t << " milliseconds." << endl;



	t = (double)getTickCount();
	for (int i = 0; i < time; i++) {
		Mat clone_i;
		clone_i = ScanImageAndReduceIterator(I, table);
	}
	t = ((double)getTickCount() - t) / getTickFrequency() * 1000;
	t /= 100;
	cout << "Time of reducing with the Iterator (averaged for "
		<< time << " runs): " << t << " milliseconds." << endl;


	t = (double)getTickCount();
	for (int i = 0; i < time; i++) {
		Mat clone_i;
		clone_i = ScanImageAndReduceRandomAccess(I, table);
	}
	t = ((double)getTickCount() - t) / getTickFrequency() * 1000;
	t /= 100;
	cout << "Time of reducing with on-the-fly address generation - at function (averaged for "
		<< time << " runs): " << t << " milliseconds." << endl;
	

	//使用opencv自带的lut函数，效果更好
	Mat LookUpTable(1, 256, CV_8U);
	uchar *p = LookUpTable.ptr();
	for (int i = 0; i < 256; i++) {
		p[i] = table[i];
	}
	t = (double)getTickCount();

	for (int i = 0; i < time; ++i)
		//! [table-use]
		LUT(I, LookUpTable, J);
	//! [table-use]

	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= time;

	cout << "Time of reducing with the LUT function (averaged for "
		<< time << " runs): " << t << " milliseconds." << endl;

	return 1;
}

//effective
Mat& ScanImageAndReduceC(Mat &I, const uchar *table) {
	CV_Assert(I.depth() ==CV_8U);
	int rows = I.rows;
	int cols = I.cols*I.channels();
	//判断是否为矩阵元素连续分配，如果连续分配，可以当作一维数组看待，操作更快
	if (I.isContinuous()) {
		cols *= rows;
		rows = 1;
	}
	uchar *p;
	for (int i = 0; i < rows; i++) {
		p = I.ptr<uchar>(i);
		for (int j = 0; j < cols; ++j) {
			p[j] = table[p[j]];
		}
	}
	return I;
}

//reducing with the Iterator Safer
Mat& ScanImageAndReduceIterator(Mat &I, const uchar *table) {
	CV_Assert(I.depth() == CV_8U);
	int channels = I.channels();
	int rows = I.rows;
	int cols = I.cols;
	switch (channels)
	{
	case 1:
	{
		MatIterator_<uchar> it, end;
		for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; it++) {
			*it = table[*it];
		}
		break;
	}
	case 3:
	{
		MatIterator_<Vec3b> it, end;
		for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; it++) {
			(*it)[0] = table[(*it)[0]];
			(*it)[1] = table[(*it)[1]];
			(*it)[2] = table[(*it)[2]];
		}
	}
	}
	return I;
}

//not recommend
Mat &ScanImageAndReduceRandomAccess(Mat &I, const uchar *table) {
	CV_Assert(I.depth() == CV_8U);
	int channels = I.channels();
	switch (channels)
	{
	case 1:
	{

		for (int i = 0; i < I.rows; ++i) {
			for (int j = 0; j < I.cols; ++j) {
				I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
			}
		}
		break;
	}
	case 3:
	{
		//使用Mat_ 遍历矩阵更快，操作更方便，代码量也更小
		Mat_<Vec3b> _I=I;
		for (int i = 0; i < I.rows; ++i) 
		{
			for (int j = 0; j < I.cols; ++j) 
			{
				_I(i, j)[0] = table[_I(i, j)[0]];
				_I(i, j)[1] = table[_I(i, j)[1]];
				_I(i, j)[2] = table[_I(i, j)[2]];
			}
		}
	}
	}
	return I;
}
