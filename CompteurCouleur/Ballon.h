#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#include <vector>

using namespace cv;
using std::vector;

class Ballon {
private:
	Point d_center;
	int d_radius;
	Scalar d_color;
public:
	Ballon(Point center, int radius, Scalar color);
	void deplaceY(int step);
	void deplaceX(int step);
	Point center();
	Scalar color();
	void setColor(Scalar color);
	vector<vector<Point>> getContour(const Mat& image);
	bool isHit(const Point& p);
	void draw(const Mat& image);
};