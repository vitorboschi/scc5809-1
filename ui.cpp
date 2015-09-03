#include "ui.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

static void onMouse( int event, int x, int y, int, void* parameter) {
	static bool isMouseDown = false;
	static int lastX = 0;
	static int lastY = 0;
	static cv::Mat reducedImage(8, 8, CV_8UC1);
	static cv::Mat roiImage;

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
		
		boundRect[0] = cv::boundingRect(contours[0]);

		roiImage = (*canvas)(boundRect[0]);
		resize(roiImage, reducedImage, reducedImage.size(), 0, 0, CV_INTER_AREA);
		imshow("roiImage", roiImage);
		imshow("canvas", *canvas);
		std::cout << "Matriz: " << reducedImage << std::endl;
		cv::rectangle(*canvas, boundRect[0].tl(), boundRect[0].br(), cv::Scalar(255), 1, 8, 0 );
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
	cv::namedWindow("roiImage", 0);
	imshow("canvas", canvas);
	cv::setMouseCallback("canvas", onMouse, &canvas);
	cv::waitKey(0);
		
}

