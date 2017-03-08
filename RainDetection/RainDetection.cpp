// RainDetection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

string rainDropsCascadeName = "raindrops_cascade_night_300_100_21_haar.xml";
//string rainDropsCascadeName = "raindrops_cascade_daylight_300_100_30.xml";
CascadeClassifier raindropsCascade;


void detectAndDisplay(Mat frame)
{
	std::vector<Rect> drops;
	Mat gray;

	cvtColor(frame, gray, CV_BGR2GRAY);
	equalizeHist(gray, gray);

	//-- Detect faces
	raindropsCascade.detectMultiScale(gray, drops, 1.1, 1, 0, Size(1,1), Size(48,48));

	cout << "drops count : " << drops.size() << endl;

	for (size_t i = 0; i < drops.size(); i++)
	{
		Point center(drops[i].x + drops[i].width*0.5, drops[i].y + drops[i].height*0.5);
		ellipse(frame, center, Size(drops[i].width*0.5, drops[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 1, 8, 0);
	}
	//-- Show what you got
	//namedWindow("Raindrops", 0);
	imshow("Raindrops", frame);
}

int _tmain(int argc, _TCHAR* argv[])
{
	VideoCapture capture("test/PX_test/MOV_0004-1.MOV");//¼v¤ù¸ô®|
	Mat frame;
	Mat image;
	Mat imageROI, imageGray, imageBin;

	//-- 1. Load the cascades
	if (!raindropsCascade.load(rainDropsCascadeName)) {
		cout << "Cannot load cascade file !!!" << endl;
		system("pause");
		return -1;
	}

	image = imread("0130.jpg");
	cvtColor(image, imageGray, CV_BGR2GRAY);
	//threshold(imageGray, )
	//namedWindow("Image", 0);
	imshow("Image", imageGray);

	imageROI = image(Rect(0, 0, image.cols, image.rows * 0.67));
	resize(imageROI, imageROI, Size(1920, 720));


	detectAndDisplay(imageROI);


	if (!capture.isOpened())
	{
	cout << "fail to open!" << endl;
	return -1;
	}

	/*cvNamedWindow("Src", 0);
	for (;;) {
	capture >> frame;
	//frame += Scalar(75, 75, 75);
	Mat roi = frame(Rect(0, 0, frame.cols, frame.rows / 2));
	if (!frame.empty()) {
	imshow("Src", roi);
	detectAndDisplay(roi);
	}

	waitKey(33);
	}*/
	
	waitKey(0);
	return 0;
}

