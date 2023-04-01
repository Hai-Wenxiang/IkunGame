#include "goods_load.h"

cv::Mat getWood01Mat(unsigned int state)
{
    static cv::Mat wood01Mat[] = {
        cv::imread("pictures/goods/wood01_00.png"),
    };
    if (state < sizeof(wood01Mat) / sizeof(wood01Mat[0])) {
        addAlpha(wood01Mat[state]);
        return wood01Mat[state];
    }

    return getDefaultMat();
}
