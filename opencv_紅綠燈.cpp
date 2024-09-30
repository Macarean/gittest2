#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<iomanip>

#define CV_PI   3.1415926535897932384626433832795

using namespace std;
using namespace cv;
int main(int argc, char* argv[])
{

	Mat img, img2, blue, red1, red2, red3, yellow, yellow1, black, img3, img4, img5;
	vector<vector<Point>> contours;
	vector<Vec4i>end;
	vector<Rect>boundRect;
	vector<Rect>boundRect2;
	Rect buffer;
	vector<int>record;
	img = imread("public4.jpg", IMREAD_COLOR);
	//img = imread(argv[1], IMREAD_COLOR);
	cvtColor(img, img2, COLOR_BGR2HSV); // Convert to gray

	//blue
	/*inRange(img2, Scalar(40, 30, 90), Scalar(160, 255, 255), blue);*/
	inRange(img2, Scalar(105, 110, 70), Scalar(121, 255, 255), blue);
	threshold(blue, blue, 160, 255, THRESH_BINARY);//無法去除陰影
	findContours(blue, contours, end, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); i++) {
		double a = contourArea(contours[i], false);
		if (a < 800) {
			drawContours(blue, contours, i, Scalar(0, 0, 0), -1, 8);
		}
		else {
			buffer = boundingRect(contours[i]);
			buffer.x -= 6;
			buffer.y -= 6;
			buffer.width += 9;
			buffer.height += 9;
			boundRect2.push_back(buffer);
			record.push_back(buffer.x);
		}
	}

	inRange(img2, Scalar(170, 10, 10), Scalar(210, 255, 255), red1);
	inRange(img2, Scalar(0, 90, 50), Scalar(10, 255, 255), red2);
	bitwise_or(red1, red2, red3);


	contours.clear();
	end.clear();
	threshold(red3, red3, 160, 255, THRESH_BINARY);//無法去除陰影
	findContours(red3, contours, end, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); i++) {
		double a = contourArea(contours[i], false);
		if (a < 800) {
			drawContours(red3, contours, i, Scalar(0, 0, 0), -1, 8);
		}
		else {
			buffer = boundingRect(contours[i]);
			buffer.x -= 7;
			buffer.y -= 4;
			buffer.width += 14;
			buffer.height += 7;
			boundRect2.push_back(buffer);
			record.push_back(buffer.x);
		}
	}


	//yellow
	inRange(img2, Scalar(15, 150, 190), Scalar(40, 255, 255), yellow);
	
	contours.clear();
	end.clear();
	threshold(yellow, yellow, 160, 255, THRESH_BINARY);//無法去除陰影
	findContours(yellow, contours, end, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); i++) {
		double a = contourArea(contours[i], false);
		if (a < 800) {
			drawContours(img4, contours, i, Scalar(0, 0, 0), -1, 8);
		}
		else {
			buffer = boundingRect(contours[i]);
			buffer.x -= 10;
			buffer.y -= 10;
			buffer.width += 21;
			buffer.height += 18;
			boundRect.push_back(buffer);
			record.push_back(buffer.x);
			boundRect2.push_back(buffer);
		}
	}


	/*int cen_x;
	int cen_y;
	for (int i = 0; i < boundRect.size(); i++) {
		cen_x = boundRect[i].x + boundRect[i].width / 2;
		cen_y= boundRect[i].y + boundRect[i].height / 2;
		boundRect[i].width /= 0.73;
		boundRect[i].height/= 0.73;
		boundRect[i].x = cen_x- boundRect[i].width/2;
		boundRect[i].y = cen_y- boundRect[i].height/2;
		record.push_back(boundRect[i].x);
		boundRect2.push_back(boundRect[i]);
	}*/
	
	

	for (int i = 0; i < boundRect2.size(); i++) {
		rectangle(img, boundRect2[i], Scalar(0, 0, 255));
	}
	
	//cout << endl<<boundRect[0].x << " " << boundRect[0].y << " " << boundRect[0].width << " " << boundRect[0].height<<endl;
	sort(record.begin(), record.end());
	vector<Rect>boundRect3;
	for (int i = 0; i < record.size(); i++) {
		for (int j = 0; j < boundRect2.size(); j++) {
			if (boundRect2[j].x == record[i]) {
				boundRect3.push_back(boundRect2[j]);
				break;
			}
		}
	}

	for (int i = 0; i < boundRect3.size(); i++) {
		cout << endl << boundRect3[i].x << " " << boundRect3[i].y << " " << boundRect3[i].x + boundRect3[i].width << " " << boundRect3[i].y + boundRect3[i].height << endl;
	}
	/*buffer.x = 46;
	buffer.y = 90;
	buffer.width = 148;
	buffer.height = 128;
	rectangle(img, buffer, Scalar(0, 0, 255));*/
	/*namedWindow("Display", 0);
	resizeWindow("Display", 500, 500);*/
	imshow("Display", img);
	waitKey(0);
	return 0;
}