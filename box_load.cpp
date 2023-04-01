#include "box_load.h"

/* 水域-平坦 */
cv::Mat getWaterPlainMat(void)
{
    static cv::Mat waterPlainMat = cv::imread("pictures/box/water/plain.png");
    return waterPlainMat;
}

/* 水域-未知 */
cv::Mat getWaterUnknownMat(void)
{
    static cv::Mat waterUnknownMat = cv::imread("pictures/box/water/unknown.png");
    return waterUnknownMat;
}

/* 水域-冰块 */
cv::Mat getWaterIceMat(void)
{
    static cv::Mat waterIceMat = cv::imread("pictures/box/water/ice.png");
    return waterIceMat;
}

/* 水域-木头01 */
cv::Mat getWaterWood01Mat(void)
{
    static cv::Mat waterWood01Mat = cv::imread("pictures/box/water/wood01.png");
    return waterWood01Mat;
}