#include "goods_load.h"

cv::Mat getWood01Mat(unsigned int state)
{
    static cv::Mat wood01Mat[] = {
        cv::imread("pictures/goods/wood01_00.png", cv::IMREAD_UNCHANGED),
    };
    if (state < sizeof(wood01Mat) / sizeof(wood01Mat[0])) {
        return wood01Mat[state];
    }

    return getDefaultMat();
}
