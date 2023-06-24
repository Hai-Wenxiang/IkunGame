#include "composition_table.h"

CompositionTable::CompositionTable(void)
{
	state = (char)0;
	data1 = (unsigned char)0;
	data2 = (unsigned short)0;
	return;
}

CompositionTable::~CompositionTable(void)
{
	return;
}

void CompositionTable::setState(short state)
{
	this->state = state;
	return;
}

short CompositionTable::getState(void)
{
	return state;
}

void CompositionTable::setData1(short data1)
{
	this->data1 = data1;
	return;
}

short CompositionTable::getData1(void)
{
	return data1;
}

void CompositionTable::setData2(short data2)
{
	this->data2 = data2;
	return;
}

short CompositionTable::getData2(void)
{
	return data2;
}

// 合成
static void compose(int data1, int data2, Bag& bag)
{
	return;
}

bool CompositionTable::parseKey(int key, Bag& bag)
{
	// 按c键进入合成界面
	switch (state) {
	case 0: // 不在这里
		if (key != 'c') {
			return false;
		}
		state = 1;
		break;
	case 1: // 选类别
		if (key == 'a' || key == 'd') {
			data1 += COMPOSITIONDATA1NUM + (key == 'a' ? (-1) : 1);
			data1 %= COMPOSITIONDATA1NUM;
			data2 = 0;
		}
		else if (key == ENTER || key == ESC) {
			state = key == ENTER ? 2 : 0;
		}
		break;
	case 2: // 选具体合成项
		switch (key) {
		case 'a':
			if (data2 % 5 != 0) {
				data2--;
			}
			break;
		case 'd':
			if (data2 % 5 != 4) {
				data2++;
			}
			break;
		case 'w':
			if (data2 > 4) {
				data2 -= 5;
			}
			break;
		case 's':
			if (data2 + 5 < COMPOSITIONDATA2NUM) {
				data2 += 5;
			}
			break;
		case ENTER: // 合成
			compose(data1, data2, bag);
			break;
		case ESC:
			state = 1;
		default:
			break;
		}
		break;
	default:
		return false;
	}
	return true;
}

cv::Mat CompositionTable::getMat(Bag bag)
{
	int posX = (data2 % 5) * 75 + 40;
	int posY = (data2 / 5) * 75 + 115;
	int pos1 = data1 * 85 + 5;
	cv::Mat mat = getCompositionTableMat().clone();
	switch (state) {
	case 2:
		cv::arrowedLine(mat, cv::Point(pos1 + 35, 35), cv::Point(posX, posY),
			cv::Scalar(0, 0, 255), 2);
	case 1:
		cv::rectangle(mat, cv::Point(pos1, 5), cv::Point(pos1 + 75, 75),
			cv::Scalar(0, 0, 255), 2);
	case 0:
		return mat;
	default:
		return getDefaultMat();
	}
	
	return getDefaultMat();
}
