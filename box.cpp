#include "box.h"

Box::Box(unsigned short newType)
{
	type = newType;
	state = (unsigned short)0;
	stateStartTime = GetTickCount64();
	return;
}

Box::~Box(void)
{
	return;
}

void Box::setType(unsigned short newType)
{
	type = newType;
	return;
}

unsigned short Box::getType(void)
{
	return type;
}

void Box::setState(unsigned short newState)
{
	state = newState;
	return;
}

unsigned short Box::getState(void)
{
	return state;
}

void Box::setStateStartTime(void)
{
	stateStartTime = GetTickCount64();
}

ULONGLONG Box::getStateStartTime(void)
{
	return stateStartTime;
}

unsigned char Box::getBase(void)
{
	return (unsigned char)((type >> 12) & 0xF);
}

bool Box::isPlain(void)
{
	return (type & 0xFFF) == 0;
}

bool Box::isUnknown(void)
{
	return type & 1;
}

/* 判定水域中的非平坦已知方块是否可拾取 */
static bool canFetch_Water(unsigned short type)
{
	switch (type) {
	case WATER_ICE:
		return false;
	case WATER_WOOD_01:
		return true;
	default:
		break;
	}
	return false;
}

/* 判定方块是否可拾取 */
bool Box::canFetch(void)
{
	if (isPlain() || isUnknown()) {
		return false;
	}
	switch (getBase()) {
	case 0x0:
		return canFetch_Water(type);
	default:
		break;
	}
	return false;
}

/* 根据所属的生态，获取平坦的图片 */
static cv::Mat getPlainMatByBase(unsigned char base)
{
	switch (base) {
	case 0x0:	// 水域
		return cv::imread("pictures/box/water/plain.png");
	case 0x1:	// 深水域
	case 0x2:	// 森林
	case 0x3:	// 深森林
	case 0x4:	// 沙漠
	case 0x5:	// 深沙漠
	default:
		return cv::imread("pictures/default.png");
	}
}

static cv::Mat getUnknownMatByBase(unsigned int base)
{
	switch (base) {
	case 0x0:	// 水域
		return cv::imread("pictures/box/water/unknown.png");
	case 0x1:	// 深水域
	case 0x2:	// 森林
	case 0x3:	// 深森林
	case 0x4:	// 沙漠
	case 0x5:	// 深沙漠
	default:
		return cv::imread("pictures/default.png");
	}
}

static cv::Mat getWaterMat(unsigned short type)
{
	switch (type) {
	case WATER_ICE:
		return cv::imread("pictures/box/water/ice.png");
	case WATER_WOOD_01:
		return cv::imread("pictures/box/water/wood01.png");
	default:
		break;
	}

	return cv::imread("pictures/default.png");
}

static cv::Mat getDeepWaterMat(unsigned short type)
{
	switch (type) {
	default:
		break;
	}

	return cv::imread("pictures/default.png");
}

static cv::Mat getForestMat(unsigned short type)
{
	switch (type) {
	default:
		break;
	}

	return cv::imread("pictures/default.png");
}

static cv::Mat getDeepForestMat(unsigned short type)
{
	switch (type) {
	default:
		break;
	}

	return cv::imread("pictures/default.png");
}

static cv::Mat getDesertMat(unsigned short type)
{
	switch (type) {
	default:
		break;
	}

	return cv::imread("pictures/default.png");
}

static cv::Mat getDeepDesertMat(unsigned short type)
{
	switch (type) {
	default:
		break;
	}

	return cv::imread("pictures/default.png");
}

cv::Mat Box::getMat(void)
{
	unsigned char base = getBase();
	// 平坦方块
	if (isPlain()) {
		return getPlainMatByBase(base);
	}

	// 未知方块
	if (isUnknown()) {
		return getUnknownMatByBase(base);
	}
	
	// 已知的非平坦方块
	switch (base) {
	case 0x0:	// 水域
		return getWaterMat(type);
	case 0x1:	// 深水域
		return getDeepWaterMat(type);
	case 0x2:	// 森林
		return getForestMat(type);
	case 0x3:	// 深森林
		return getDeepForestMat(type);
	case 0x4:	// 沙漠
		return getDesertMat(type);
	case 0x5:	// 深沙漠
		return getDeepDesertMat(type);
	default:
		break;
	}

	return cv::imread("pictures/default.png");
}

/* 挖掘未知方块，使其变成已知 */
void Box::dig(void)
{
	if (isUnknown()) {
		type++;
	}
	return;
}

/* 将方块属性设置为平坦 */
void Box::setPlain(void)
{
	type &= 0xF000;
	return;
}
