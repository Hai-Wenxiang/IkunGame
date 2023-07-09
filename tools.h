#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <Windows.h>
#include <opencv2/opencv.hpp>

/* ��ͼƬ���͸����ͨ�� */
void addAlpha(cv::Mat& src, unsigned char alpha = 255);

/* ���ƴ���Alphaͨ����ͼƬ����һ����Alphaͨ����ͼƬ�� */
void copyAlphaTo(cv::Mat& src, cv::Mat& dst, cv::Point pos);

/* �ı�ͼƬ��͸���� */
void changeAlpha(cv::Mat& src, unsigned char alpha);

/* ��ȡĬ��ͼƬ */
cv::Mat getDefaultMat(void);

/* ������������ */
bool mouseClickOut(void);

#endif // _TOOLS_H_
