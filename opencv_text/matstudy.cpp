#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
	//creat head
	Mat A, C;
	A = imread("picture1.png", IMREAD_COLOR);
	//copy constructor
	Mat B(A);
	//Assigment operator
	C = A;
	imshow("1", C);

	//ROI D:using a rectangle and E:using row and column boundaries
	Mat D(A, Rect(10, 10, 100, 100));
	Mat E = A(Range::all(), Range(1, 200));
	imshow("2", D);
	imshow("3", E);

	//Now modifying F and G won't effect the matrix pointed by the Mat header
	Mat F = A.clone();
	Mat G;
	A.copyTo(G);
	imshow("4", F);
	imshow("5", G);
	imshow("6", A);
	waitKey(0);
	return 0;
}
