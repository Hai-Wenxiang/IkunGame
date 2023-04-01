#include "tools.h"

void addAlpha(cv::Mat& mat)
{
	return;
	switch (mat.channels()) {
	case 1:
		cv::cvtColor(mat, mat, cv::COLOR_GRAY2BGR);
		break;
	case 3:
		cv::cvtColor(mat, mat, cv::COLOR_BGR2BGRA);
		return;
		break;
	default:
		return;
	}

	std::vector<cv::Mat> channels;
	static cv::Mat alpha(mat.size(), CV_8UC1, cv::Scalar(255));
	cv::split(mat, channels);
	channels.push_back(alpha);
	cv::merge(channels, mat);
	return;
}

cv::Mat getDefaultMat(void)
{
	static cv::Mat defaultMat = cv::imread("pictures/default.png");
	addAlpha(defaultMat);
	return defaultMat;
}
