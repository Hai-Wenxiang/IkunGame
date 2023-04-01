#include "scene_load.h"

/* 欢迎界面 */
cv::Mat getWelcomeMat(void)
{
	static cv::Mat welcomeMat = cv::imread("pictures/scene/welcome.png");
	addAlpha(welcomeMat);
	return welcomeMat;
}

/* 设置FPS界面 */
cv::Mat getSetFPSMat(void)
{
	static cv::Mat setFPSMat = cv::imread("pictures/scene/setFPS.png");
	addAlpha(setFPSMat);
	return setFPSMat;
}