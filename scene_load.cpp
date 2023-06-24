#include "scene_load.h"

/* 欢迎界面 */
cv::Mat getWelcomeMat(void)
{
	static cv::Mat welcomeMat = cv::imread("pictures/scene/Welcome.png");
	addAlpha(welcomeMat);
	return welcomeMat;
}

/* 设置FPS界面 */
cv::Mat getSetFPSMat(void)
{
	static cv::Mat setFPSMat = cv::imread("pictures/scene/SetFPS.png");
	addAlpha(setFPSMat);
	return setFPSMat;
}

cv::Mat getCompositionTableMat(void)
{
	static cv::Mat compositionTableMat = cv::imread("pictures/scene/CompositionTable.png");
	addAlpha(compositionTableMat);
	return compositionTableMat;
}
