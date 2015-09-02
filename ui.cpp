#include "ui.h"

#include <opencv2/highgui.hpp>                                                  
#include <opencv2/imgproc.hpp>                                                  
#include <opencv2/core.hpp>
#include <iostream>

static void onMouse( int event, int x, int y, int, void* parameter) {
	static bool isMouseDown = false;
	static int lastX = 0;
	static int lastY = 0;
	cv::Mat* canvas = (cv::Mat*)parameter;

	if (event == cv::EVENT_LBUTTONDOWN) {
		std::cout << "Started drawing" << std::endl;
		lastX = x;
		lastY = y;
		isMouseDown = true;
	}

	if (event == cv::EVENT_LBUTTONUP) {
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

