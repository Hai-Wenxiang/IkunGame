#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <opencv2/opencv.hpp>

/* 给图片添加透明度通道 */
void addAlpha(cv::Mat& src);

/* 复制带有Alpha通道的图片到另一个有Alpha通道的图片上 */
void copyAlphaTo(cv::Mat& src, cv::Mat& dst, cv::Point pos);

/* 获取默认图片 */
cv::Mat getDefaultMat(void);

#endif // _TOOLS_H_
