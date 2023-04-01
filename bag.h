#ifndef _BAG_H_
#define _BAG_H_

#include <opencv2/opencv.hpp>
#include "goods.h"

#define CAPACITY 8		// ��������

class Bag {
private:
	Goods goods[CAPACITY];	// ��Ʒ
	unsigned char atHand;	// �����õ���Ʒָ�򱳰��е�Ԫ��λ��


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