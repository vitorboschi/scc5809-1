#include "ui.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

static void onMouse( int event, int x, int y, int, void* parameter) {
	static bool isMouseDown = false;
	static int lastX = 0;
	static int lastY = 0;
	cv::Mat* canvas = (cv::Mat*)parameter;

	if (event == cv::EVENT_LBUTTONDOWN) {
		std::cout << "Started drawing" << std::endl;
		*canvas = cv::Scalar(0);
		lastX = x;
		lastY = y;
		isMouseDown = true;
	}

	if (event == cv::EVENT_LBUTTONUP) {
		std::vector<std::vector <cv::Point> > contours;

		findContours(*canvas, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

 		std::vector<cv::Rect> boundRect( contours.size() );
		
		for( int i = 0; i < contours.size(); i++ ) {
			boundRect[i] = cv::boundingRect(contours[i]);
			cv::rectangle(*canvas, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(255), 1, 8, 0 );

		}

		imshow("canvas", *canvas);
		std::cout << "End drawing" << std::endl;
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
	cv::namedWindow("canvas", 0);
	imshow("canvas", canvas);
	cv::setMouseCallback("canvas", onMouse, &canvas);
	cv::waitKey(0);
		
}

