#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat CreateExplicitlyImage(int row, int col);

int main() {
	// Mat is restoried by rows
	// Mat_<uchar> is for CV_8U ,Mat_<char> is for CV_8S
	// Mat_<int> is for CV_32S ,Mat_<float> is for CV_32F
	// Mat_<double> is for CV_64F 
	Mat M;
	M = CreateExplicitlyImage(2, 2);
	cout << "M " << endl << M << endl;

	//CV_8UC(1) is the same CV_8UC1
	//but when the size is more than 4 we should use parenthesis 
	int sz[3] = { 2,2,2 };
	Mat L(3, sz, CV_8UC(1), Scalar::all(0));
	
	M.create(4, 4, CV_8UC(2));
	cout << "M " <<endl<< M << endl << endl;

	
	Mat E = Mat::eye(4, 4, CV_64F); //µ¥Î»¾ØÕó
	cout << "E" << endl << E<<endl;

	Mat O = Mat::ones(2, 2, CV_32F); //È«1¾ØÕó
	cout << "O" << endl << O << endl;

	Mat Z = Mat::zeros(3, 3, CV_8UC1); //Áã¾ØÕó
	cout << "Z" << endl << Z << endl;

	//For small matrices you may use comma separated initializers 
	//or initializer lists (C++11 support is required in the last case):
	Mat C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cout << "C" << endl << C << endl<<endl;
	C = (Mat_<double>({ 0, -1, 0, -1, 5, -1, 0, -1, 0 })).reshape(3);
	cout << "C" << endl << C << endl << endl;

	//create a new header for an existing Mat object
	Mat RowClone = C.row(1).clone();
	cout << "RowClone" << endl << RowClone << endl << endl;

	//fill out a matrix with random value
	Mat R = Mat(3, 2, CV_8UC3);

	//@param InputandOutput dst
	//@param lower bound
	//@param higher bound
	randu(R, Scalar::all(0), Scalar::all(255));
	cout << "R" << endl << R<< endl << endl;


	//Output of other common items
	//2D Point
	Point2f P(5, 1);
	cout << "Point (2d)=" << P << endl << endl;
	//3d point
	Point3f P3f(5, 1,1);
	cout << "Point (3d)=" << P3f<< endl << endl;

	//vector via Mat
	vector<float> v;
	v.push_back((float)CV_PI);
	v.push_back(3);
	v.push_back(3.01f);
	cout << "vector if float via Mat =" << Mat(v) << endl << endl;

	//vector of points
	vector<Point2f> vPoints(20);
	for (size_t i = 0; i < vPoints.size(); ++i) {
		vPoints[i] = Point2f((float)(i * 5), (float)(i % 7));
	}
	cout << "A vector of 2D Points =" << vPoints << endl << endl;
	cout << endl;


	system("pause");
	return 0;
}

/*Creating a 2d Mat object explicitly
@param input row int.
@parem inpur col int.
*/
Mat CreateExplicitlyImage(int row,int col) {
	//CV_8UC3 means we use unsigned char types 
	//that are 8 bit long and each pixel has 
	//three of these to form the three channels
	Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
	return M;
}