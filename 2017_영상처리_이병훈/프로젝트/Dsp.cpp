#include <opencv2\core\core.hpp>
#include <opencv2\core\mat.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat objectHistogram;
Mat globalHistogram;

void getObjectHistogram(Mat &frame, Rect object_region)
{
	const int channels[] = { 0, 1 };
	const int histSize[] = { 64, 64 };
	float range[] = { 0, 256 };
	const float *ranges[] = { range, range };

	// ���� ���� ������׷�
	Mat objectROI = frame(object_region);
	calcHist(&objectROI, 1, channels, noArray(), objectHistogram, 2, histSize, ranges, true, false);


	// ���� ������׷��� ����� ������ ���� ����
	calcHist(&frame, 1, channels, noArray(), globalHistogram, 2, histSize, ranges, true, true);


	// �������� ���� Ȯ�������� ��� �������� ���Ǻ� Ȯ�� ���� 
	for (int y = 0; y < objectHistogram.rows; y++) {
		for (int x = 0; x < objectHistogram.cols; x++) {
			objectHistogram.at<float>(y, x) /= globalHistogram.at<float>(y, x);
		}
	}
	normalize(objectHistogram, objectHistogram, 0, 255, NORM_MINMAX);
}
void backProjection(const Mat &frame, const Mat &histogram, Mat &bp) {
	const int channels[] = { 0, 1 };
	float range[] = { 0, 256 };
	const float *ranges[] = { range, range };
	calcBackProject(&frame, 1, channels, objectHistogram, bp, ranges);
}


int main()
{
	
	VideoCapture cap(0);
	
	//��ĸ���� ĸó�Ǵ� �̹��� ũ�⸦ 320x240���� ����  
	cap.set(CAP_PROP_FRAME_WIDTH, 320);
	cap.set(CAP_PROP_FRAME_HEIGHT, 240);

	if (!cap.isOpened())
	{
		cout << "��ķ�� �� �� �����ϴ�." << endl;
		return -1;
	}
	

	namedWindow("ã�� ������ ����", CV_WINDOW_AUTOSIZE);

	//Ʈ���ٿ��� ���Ǵ� ���� �ʱ�ȭ 
	int LowH = 0;
	int HighH = 7;

	int LowS = 50;
	int HighS = 255;

	int LowV = 0;
	int HighV = 255;


	//Ʈ���� ���� 
	cvCreateTrackbar("LowH", "ã�� ������ ����", &LowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "ã�� ������ ����", &HighH, 179);

	cvCreateTrackbar("LowS", "ã�� ������ ����", &LowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "ã�� ������ ����", &HighS, 255);

	cvCreateTrackbar("LowV", "ã�� ������ ����", &LowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "ã�� ������ ����", &HighV, 255);


	Rect trackingWindow(0, 0, 30, 30);
	
	int i = 0;
	while (true)
	{
		i++;

		Mat img_input, img_hsv, img_binary;
		bool ret = cap.read(img_input);
		
				//ī�޶�κ��� �̹����� ������ 
	
	
		if (!ret)
		{
			cout << "ī�޶�κ��� �̹����� ������ �� �����ϴ�." << endl;
			break;
		}


		//HSV�� ��ȯ
		cvtColor(img_input, img_hsv, COLOR_BGR2HSV);



		//������ HSV ������ �̿��Ͽ� ������ ����ȭ
		inRange(img_hsv, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), img_binary);


		//morphological opening ���� ������ ���� 
		erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));


		//morphological closing ������ ���� �޿�� 
		dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));



		if (i < 100)
		{

			//�󺧸� 
			Mat img_labels, stats, centroids;
			int numOfLables = connectedComponentsWithStats(img_binary, img_labels,
				stats, centroids, 8, CV_32S);


			//�����ڽ� �׸���
			int max = -1, idx = 0;
			for (int j = 1; j < numOfLables; j++) {
				int area = stats.at<int>(j, CC_STAT_AREA);
				if (max < area)
				{
					max = area;
					idx = j;
				}
			}


			int left = stats.at<int>(idx, CC_STAT_LEFT);
			int top = stats.at<int>(idx, CC_STAT_TOP);
			int width = stats.at<int>(idx, CC_STAT_WIDTH);
			int height = stats.at<int>(idx, CC_STAT_HEIGHT);


			rectangle(img_input, Point(left, top), Point(left + width, top + height),
				Scalar(0, 0, 255), 1);

			Rect object_region(left, top, width, height);
			cout << "������׷� �����" << endl;
			getObjectHistogram(img_hsv, object_region);
			trackingWindow = object_region;
		}
		else {
			Mat bp;
			backProjection(img_hsv, objectHistogram, bp);

			// Tracking
			cout << "tracking�� �����մϴ�" << endl;
			meanShift(bp, trackingWindow, TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 100, 0.01));
			rectangle(img_input, trackingWindow, CV_RGB(0, 0, 255), 2);
		}

		imshow("����ȭ ����", img_binary);
		imshow("���� ����", img_input);


		//ESCŰ ������ ���α׷� ����
		if (waitKey(1) == 27)
			break;
		
		}

	
	return 0;
}


