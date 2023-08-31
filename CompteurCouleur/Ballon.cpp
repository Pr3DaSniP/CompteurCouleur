#include "Ballon.h"

Ballon::Ballon(Point center, int radius, Scalar color) 
	: d_center{ center }, d_radius{ radius }, d_color{ color } 
{}

void Ballon::deplaceY(int step) {
	d_center.y += step;
}

void Ballon::deplaceX(int step) {
	d_center.x += step;
}

Point Ballon::center() {
	return d_center;
}

Scalar Ballon::color() {
	return d_color;
}

void Ballon::setColor(Scalar color) {
	d_color = color;
}

vector<vector<Point>> Ballon::getContour(const Mat& image) {
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	Mat1b masque;
	inRange(hsv, Scalar(40, 40, 40), Scalar(70, 255, 255), masque);
	vector<vector<Point>> contours;
	findContours(masque, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	return contours;
}

bool Ballon::isHit(const Point& p) {
	return norm(p - d_center) < d_radius;
}

void Ballon::draw(const Mat& image) {
	circle(image, d_center, d_radius, d_color, FILLED);
}