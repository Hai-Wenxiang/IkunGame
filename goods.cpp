#include "goods.h"

Goods::Goods(void)
{
	type = 0;
	state = 0;
	num = 0;
	return;
}

Goods::~Goods(void)
{
	type = 0;
	state = 0;
	num = 0;
	return;
}

void Goods::setType(unsigned int newType)
{
	type = newType;
	return;
}

unsigned int Goods::getType(void)
{
	return type;
}

void Goods::setState(unsigned int newState)
{
	state = newState;
	return;
}

unsigned int Goods::getState(void)
{
	return state;
}

void Goods::setNum(unsigned int newNum)
{
	num = newNum;
	return;
}

unsigned int Goods::getNum(void)
{
	return num;
}

bool Goods::equals(Goods goods)
{
	return (type == goods.getType()) && (state == goods.getState());
}

bool Goods::add(unsigned int add)
{
	if (num + add <= MAXGOODSNUM) {
		num += add;
		return true;
	}
	return false;
}

bool Goods::sub(unsigned int sub)
{
	if (sub <= num) {
		num -= sub;
		return true;
	}
	return false;
}

static cv::Mat getDefaultGoodsMat(void)
{
	static cv::Mat defaultGoodsMat =
		cv::Mat(60, 60, CV_8UC4, cv::Scalar(0, 0, 0, 0));
	return defaultGoodsMat;
}

cv::Mat Goods::getMat(void)
{
	switch (type) {
	case 1:
		return getWood01Mat(state);
	default:
		break;
	}
	return getDefaultGoodsMat();
}
