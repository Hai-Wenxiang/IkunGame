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
	for (int i = 0; i < CAPACITY; i++) {
		// 绘制框
		cv::rectangle(gameMat,
			cv::Point(180 + i * 70, 700),
			cv::Point(250 + i * 70, 770),
			cv::Scalar(127, 127, 127),
			3);
		// 绘制物品
		if (goods[i].getType() > 0) {
			goods[i].getMat().copyTo(gameMat(cv::Rect(
				185 + i * 60,
				710,
				60,
				60
				)));
		}
		// 绘制数量
		cv::putText(gameMat,
			std::to_string(goods[i].getNum()),
			cv::Point(184 + i * 70, 718),
			cv::FONT_HERSHEY_SIMPLEX,
			0.55,
			cv::Scalar(255, 0, 0));

		// 绘制手握部分

	}
	return;
}
