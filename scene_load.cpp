#include "scene_load.h"

/* ��ӭ���� */
cv::Mat getWelcomeMat(void)
{
	static cv::Mat welcomeMat = cv::imread("pictures/scene/welcome.png");
	addAlpha(welcomeMat);
	return welcomeMat;
}

/* ����FPS���� */
cv::Mat getSetFPSMat(void)
{
	static cv::Mat setFPSMat = cv::imread("pictures/scene/setFPS.png");
	addAlpha(setFPSMat);
	return setFPSMat;
}