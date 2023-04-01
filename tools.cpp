#include "tools.h"

void addAlpha(cv::Mat& src)
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
	dstChannels.push_back(cv::Mat(src.rows, src.cols, CV_8UC1, cv::Scalar(255)));
	//合并通道
	cv::merge(dstChannels, dst);
	src = dst;
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
