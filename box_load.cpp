#include "box_load.h"

/* ˮ��-ƽ̹ */
cv::Mat getWaterPlainMat(void)
{
    static cv::Mat waterPlainMat = cv::imread("pictures/box/water/plain.png");
    return waterPlainMat;
}

/* ˮ��-δ֪ */
cv::Mat getWaterUnknownMat(void)
{
    static cv::Mat waterUnknownMat = cv::imread("pictures/box/water/unknown.png");
    return waterUnknownMat;
}

/* ˮ��-���� */
cv::Mat getWaterIceMat(void)
{
    static cv::Mat waterIceMat = cv::imread("pictures/box/water/ice.png");
    return waterIceMat;
}

/* ˮ��-ľͷ01 */
cv::Mat getWaterWood01Mat(void)
{
    static cv::Mat waterWood01Mat = cv::imread("pictures/box/water/wood01.png");
    return waterWood01Mat;
}