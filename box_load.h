#ifndef _BOX_LOAD_H_
#define _BOX_LOAD_H_

#include <opencv2/opencv.hpp>
#include "tools.h"

/* ˮ��ͼƬ */
cv::Mat getWaterPlainMat(void);
cv::Mat getWaterUnknownMat(void);
cv::Mat getWaterIceMat(void);
cv::Mat getWaterWood01Mat(void);

#endif // _BOX_LOAD_H_