#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <opencv2/opencv.hpp>

/* ��ͼƬ���͸����ͨ�� */
void addAlpha(cv::Mat& src);

/* ���ƴ���Alphaͨ����ͼƬ����һ����Alphaͨ����ͼƬ�� */
void copyAlphaTo(cv::Mat& src, cv::Mat& dst, cv::Point pos);

/* ��ȡĬ��ͼƬ */
cv::Mat getDefaultMat(void);

#endif // _TOOLS_H_
