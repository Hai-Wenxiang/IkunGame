#include "bag.h"

Bag::Bag(void)
{
	for (int i = 0; i < CAPACITY; i++) {
		goods[i] = Goods();
	}
	atHand = 0;
	return;
}

Bag::~Bag(void)
{
	for (int i = 0; i < CAPACITY; i++) {
		goods[i].~Goods();
	}
	atHand = 0;
	return;
}

void Bag::setAtHandLeft(void)
{
	if (atHand > 0) {
		atHand--;
	}
	else {
		atHand = CAPACITY - 1;
	}
	return;
}

void Bag::setAtHandRight(void)
{
	if (atHand < CAPACITY - 1) {
		atHand++;
	}
	else {
		atHand = 0;
	}
	return;
}

unsigned char Bag::getAtHand(void)
{
	return atHand;
}

/* 把物品放进背包，返回是否成果放入 */
bool Bag::putGoodsIn(Goods newGoods)
{
	if (newGoods.getType() == 0 || newGoods.getNum() == 0) {
		return false;
	}

	if (goods[atHand].equals(newGoods)) {
		if (goods[atHand].add(newGoods.getNum())) {
			return true;
		}
	}

	if (goods[atHand].getType() == 0) {
		goods[atHand] = newGoods;
		return true;
	}

	for (int i = 0; i < CAPACITY; i++) {
		if (goods[i].equals(newGoods) && goods[i].add(newGoods.getNum())) {
			return true;
		}
	}

	for (int i = 0; i < CAPACITY; i++) {
		if (goods[i].getType() == 0) {
			goods[i] = newGoods;
			return true;
		}
	}

	return false;
}

Goods Bag::throwAway(void)
{
	Goods throwGoods = goods[atHand];
	goods[atHand] = Goods();
	return throwGoods;
}

/* 在游戏图中绘制背包状态 */
void Bag::paintBagInGame(cv::Mat& gameMat)
{
	cv::Mat goodsMat;
	for (int i = 0; i < CAPACITY; i++) {
		// 绘制框
		cv::rectangle(gameMat,
			cv::Point(180 + i * 70, 700),
			cv::Point(250 + i * 70, 770),
			cv::Scalar(127, 127, 127),
			3);
		// 绘制物品
		if (goods[i].getType() > 0) {
			goodsMat = goods[i].getMat();
			copyAlphaTo(goodsMat, gameMat, cv::Point(185 + i * 70, 710));
		}
		// 绘制数量
		cv::putText(gameMat,
			std::to_string(goods[i].getNum()),
			cv::Point(185 + i * 70, 720),
			cv::FONT_HERSHEY_SIMPLEX,
			0.55,
			cv::Scalar(255, 0, 0),
			2);
	}

	// 重新绘制在手上的那个框
	cv::rectangle(gameMat,
		cv::Point(180 + atHand * 70, 700),
		cv::Point(250 + atHand * 70, 770),
		cv::Scalar(200, 200, 200),
		5);

	// 绘制手握部分
	goodsMat = goods[atHand].getMat();
	copyAlphaTo(goodsMat, gameMat, cv::Point(50, 710));

	return;
}

void Bag::tidyUp(void)
{
	for (int i = 0; i < CAPACITY; i++) {
		for (int j = i + 1; j < CAPACITY; j++) {
			if (goods[i].getType() == 0 || goods[i].getNum() == 0) {
				goods[i] = goods[j];
				goods[j] = Goods();
				continue;
			}
			if (!goods[i].equals(goods[j])) {
				continue;
			}
			if (goods[i].getNum() < MAXGOODSNUM) {
				unsigned long long tot = (unsigned long long)goods[i].getNum() +
					(unsigned long long)goods[j].getNum();
				if (tot > MAXGOODSNUM) {
					goods[i].setNum(MAXGOODSNUM);
				}
				else {
					goods[i].setNum(tot);
					goods[j] = Goods();
				}
			}
		}
	}
	return;
}
