#include <opencv2\opencv.hpp>
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;


int main()
{

	double scale = 3.5;

	CascadeClassifier faceCascade;
	faceCascade.load("C:\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml");

	VideoCapture cap(0);

	if (!cap.isOpened())
		return -1;

	for (;;)
	{
		Mat frame;
		cap >> frame;
		Mat grayScale;

		cvtColor(frame, grayScale, COLOR_BGR2GRAY);
		resize(grayScale, grayScale, Size(grayScale.size().width / scale, grayScale.size().height / scale));

		vector<Rect>faces;
		faceCascade.detectMultiScale(grayScale, faces, 1.1, 3, 0, Size(30, 30));

		for (Rect area : faces)
		{
			Scalar drawColor = Scalar(255, 0, 0);
			rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)),
				Point(cvRound((area.x + area.width - 1) * scale), cvRound((area.y + area.height - 1) * scale)), drawColor);
		}

		imshow("Webcam Frame", frame);

		if (waitKey(30) >= 0)
			break;
	}
	return 0;

}