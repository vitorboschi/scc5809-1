#include "ui.h"
#include "perceptron.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

extern Perceptron p;

void mat2array(cv::Mat& m, int* a) {
	const unsigned char* mData = m.ptr<unsigned char>();

	for (int i=0;i<8*8;i++) {
		a[i] = (mData[i] > 0) ? 1 : 0; 
	}
}

static void onMouse( int event, int x, int y, int, void* parameter) {
	static bool isMouseDown = false;
	static int lastX = 0;
	static int lastY = 0;
	static cv::Mat reducedImage(8, 8, CV_8UC1);
	static cv::Mat roiImage;
	int testData[8*8];

	cv::Mat* canvas = (cv::Mat*)parameter;

	if (event == cv::EVENT_LBUTTONDOWN) {
		*canvas = cv::Scalar(0);
		lastX = x;
		lastY = y;
		isMouseDown = true;
	}

	if (event == cv::EVENT_LBUTTONUP) {
		std::vector<std::vector <cv::Point> > contours;

		findContours(*canvas, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

 		std::vector<cv::Rect> boundRect( contours.size() );
		
		boundRect[0] = cv::boundingRect(contours[0]);

		roiImage = (*canvas)(boundRect[0]);
		resize(roiImage, reducedImage, reducedImage.size(), 0, 0, CV_INTER_AREA);
		mat2array(reducedImage, testData);
		if (p.evaluateData(testData) == 1) {
			std::cout << "Up!" << std::endl;
			putText(*canvas, "UP!", cv::Point(10, 50), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255));
		}
		else {
			std::cout << "Down!" << std::endl;
			putText(*canvas, "DOWN!", cv::Point(10, 50), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255));
		}

		imshow("canvas", *canvas);
		isMouseDown = false;


	}

	if (isMouseDown) {
		cv::line(*canvas, cv::Point(x, y), cv::Point(lastX, lastY), cv::Scalar(255));
		imshow("canvas", *canvas);
		lastX = x;
		lastY = y;
	}

}

void startUI() {
	cv::Mat	canvas = cv::Mat::ones(600, 600, CV_8UC1);
	imshow("canvas", canvas);
	cv::setMouseCallback("canvas", onMouse, &canvas);
	cv::waitKey(0);
}

