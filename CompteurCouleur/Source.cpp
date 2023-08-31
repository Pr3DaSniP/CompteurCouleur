#include <iostream>
#include <windows.h>

#include "Ballon.h"
#include "Score.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

int main() {

	namedWindow("Compteur de couleur", WINDOW_AUTOSIZE);
	namedWindow("Selecteur", WINDOW_AUTOSIZE);

	int LowH1 = 0;
	int HighH1 = 255;

	int LowH2 = 0;
	int HighH2 = 255;

	createTrackbar("LowH1", "Selecteur", &LowH1, 255);
	createTrackbar("HighH1", "Selecteur", &HighH1, 255);

	createTrackbar("LowH2", "Selecteur", &LowH2, 255);
	createTrackbar("HighH2", "Selecteur", &HighH2, 255);
	
	
	Mat image;
	VideoCapture cap;
	cap.set(CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CAP_PROP_FRAME_HEIGHT, 480);
	cap.open(0);

	cap >> image;

	vector<Scalar> colors = {
		Scalar(0, 0, 255),
		Scalar(0, 255, 0),
		Scalar(255, 0, 0),
		Scalar(255, 255, 0),
		Scalar(255, 0, 255),
		Scalar(0, 255, 255),
	};

	srand(time(NULL));

	Score score{ 0 };

	int step = -5;

	Ballon* b = new Ballon{
		Point(rand() % image.cols, image.rows),
		25,
		colors[rand() % colors.size()]
	};

	bool start = false;
	
	while (1) {
		try {
			cap >> image;

			Mat hsv;
			cvtColor(image, hsv, COLOR_BGR2HSV);
			Mat1b masqueVert, masqueBleu, masqueBallon;

			if (GetAsyncKeyState('X')) {
				start = !start;
			}
			inRange(hsv, Scalar(LowH1, 0, 0), Scalar(HighH1, 255, 255), masqueVert);
			inRange(hsv, Scalar(LowH2, 0, 0), Scalar(HighH2, 255, 255), masqueBleu);
			//inRange(hsv, Scalar(40, 40, 40), Scalar(70, 255, 255), masqueVert);
			//inRange(hsv, Scalar(64, 167, 0), Scalar(130, 255, 255), masqueBleu);
			
			int nbPixelsVerts = countNonZero(masqueVert) + 1;
			int nbPixelsBleus = countNonZero(masqueBleu) + 1;

			int largeurBarre = 50;
			int hauteurBarre = image.rows;
			
			int hauteurBarreVerte = nbPixelsVerts / hauteurBarre;
			int hauteurBarreBleue = nbPixelsBleus / hauteurBarre;
			
			rectangle(image, Point(0, image.rows), Point(largeurBarre, image.rows - hauteurBarreVerte), Scalar(0, 255, 0), -1);
			rectangle(image, Point(image.cols - largeurBarre, image.rows), Point(image.cols, image.rows - hauteurBarreBleue), Scalar(255, 0, 0), -1);
			
			// 
			//		0												image.cols
			//		|													  |
			//		|-----------------------------------------------------|
			//		|													  |
			//	100% du vert										100% du bleu
			//
			
			double pourcentVert = (nbPixelsVerts) / (static_cast<double>(image.cols) * image.rows);
			double pourcentBleu = (nbPixelsBleus) / (static_cast<double>(image.cols * image.rows));			
			
			int xBalle = image.cols - (pourcentVert * image.cols);
			xBalle = xBalle - (image.cols - (pourcentBleu * image.cols));
			xBalle = xBalle + (image.cols / 2);
			int yBalle = image.rows / 4;

			if (xBalle < 0) xBalle = 0;
			if (xBalle > image.cols) xBalle = image.cols;

			circle(image, Point(xBalle, yBalle), 50, Scalar(255, 255, 255), -1);
			circle(image, Point(xBalle, yBalle), 40, Scalar(220, 220, 220), -1);

			if (start) {
				inRange(hsv, Scalar(40, 40, 40), Scalar(70, 255, 255), masqueBallon);
				vector<vector<Point>> c;
				findContours(masqueBallon, c, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

				if (c.size() > 0) {
					int max = 0;
					for (int i = 1; i < c.size(); i++) {
						if (contourArea(c[i]) > contourArea(c[max])) {
							max = i;
						}
					}

					if (b->isHit(Point(xBalle, yBalle))) {
						score.incremente();
						b = new Ballon{
							Point(rand() % image.cols, image.rows),
							10 + rand() % 40,
							colors[rand() % colors.size()]
						};

						if (score.value() % 3 == 0) {
							step -= 5;
						}

					}
				}
				putText(
					image, 
					score.toString(), 
					Point(
						xBalle - 10,
						yBalle + 10
					), 
					FONT_HERSHEY_SIMPLEX, 
					1, 
					Scalar(0, 0, 255), 
					2
				);

				b->draw(image);

				b->deplaceY(step);

				if (b->center().y < 0) break;

			}
			
			imshow("Masque vert", masqueVert);
			imshow("Masque bleu", masqueBleu);
			imshow("Compteur de couleur", image);

			waitKey(1);
		}
		catch (Exception& e) {
			cout << e.what() << endl;
		}
	}
		
	Mat endScreen = Mat::zeros(480, 640, CV_8UC3);

	putText(endScreen, "GAME OVER", Point(100, 100), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 255), 2);
	putText(endScreen, "Score : " + score.toString(), Point(100, 200), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 255), 2);

	imshow("Compteur de couleur", endScreen);
	
	waitKey(0);

	destroyAllWindows();
	
	return 0;
}