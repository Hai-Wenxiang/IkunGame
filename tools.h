#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <opencv2/opencv.hpp>

/* 给图片添加透明度通道 */
void addAlpha(cv::Mat& mat);

/* 获取默认图片 */
cv::Mat getDefaultMat(void);

#endif // _TOOLS_H_
