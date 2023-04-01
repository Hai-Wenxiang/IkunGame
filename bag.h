#ifndef _BAG_H_
#define _BAG_H_

#include <opencv2/opencv.hpp>
#include "goods.h"

#define CAPACITY 8		// 背包容量

class Bag {
private:
	Goods goods[CAPACITY];	// 物品
	unsigned char atHand;	// 手中拿的物品指向背包中的元素位置


public:
	Bag(void);
	~Bag(void);

	void setAtHandLeft(void);
	void setAtHandRight(void);
	unsigned char getAtHand(void);

	bool putGoodsIn(Goods newGoods);
	Goods throwAway(void);
	void paintBagInGame(cv::Mat& gameMat);
};

#endif // _BAG_H_