#include "tools.h"

void addAlpha(cv::Mat& src, unsigned char alpha)
{
	switch (src.channels()) {
	case 1:
		cv::cvtColor(src, src, cv::COLOR_GRAY2RGB);
	case 3:
		break;
	default:
		return;
	}

	cv::Mat dst = cv::Mat(src.rows, src.cols, CV_8UC4);

	std::vector<cv::Mat> srcChannels;
	std::vector<cv::Mat> dstChannels;
	//分离通道
	cv::split(src, srcChannels);

	dstChannels.push_back(srcChannels[0]);
	dstChannels.push_back(srcChannels[1]);
	dstChannels.push_back(srcChannels[2]);
	//添加透明度通道
	dstChannels.push_back(cv::Mat(src.rows, src.cols, CV_8UC1, cv::Scalar(alpha)));
	//合并通道
	cv::merge(dstChannels, dst);
	src = dst;
	return;
}

void changeAlpha(cv::Mat& src, unsigned char alpha)
{
	switch (src.channels()) {
	case 1:
	case 3:
		addAlpha(src, alpha);
		break;
	case 4:
		break;
	default:
		return;
	}

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			src.at<cv::Vec4b>(i, j)[3] = alpha;
		}
	}
	return;
}

void copyAlphaTo(cv::Mat& src, cv::Mat& dst, cv::Point pos)
{
	int alpha;
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			alpha = src.at<cv::Vec4b>(i, j)[3];
			for (int k = 0; k < 3; k++) {
				dst.at<cv::Vec4b>(i + pos.y, j + pos.x)[k] = (uchar)
					((alpha * src.at<cv::Vec4b>(i, j)[k] +
					(255 - alpha) * dst.at<cv::Vec4b>(i + pos.y, j + pos.x)[k]) / 255);
			}
		}
	}
	return;
}

cv::Mat getDefaultMat(void)
{
	static cv::Mat defaultMat = cv::imread("pictures/default.png");
	addAlpha(defaultMat);
	return defaultMat;
}

bool mouseClickOut(void)
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		int x, y;
		POINT mousePoint;
		HWND hwnd = FindWindowA(NULL, "Game");

		GetCursorPos(&mousePoint);
		ScreenToClient(hwnd, &mousePoint);
		x = mousePoint.x;
		y = mousePoint.y;
		if (x < 0 || x > 1260 || y < 0 || y > 800) {
			return true;
		}
	}
	return false;
}
