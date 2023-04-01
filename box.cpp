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

/* �ж�ˮ���еķ�ƽ̹��֪�����Ƿ��ʰȡ */
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

/* �ж������Ƿ��ʰȡ */
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

/* ������������̬����ȡƽ̹��ͼƬ */
static cv::Mat getPlainMatByBase(unsigned char base)
{
	switch (base) {
	case 0x0:	// ˮ��
		return cv::imread("pictures/box/water/plain.png");
	case 0x1:	// ��ˮ��
	case 0x2:	// ɭ��
	case 0x3:	// ��ɭ��
	case 0x4:	// ɳĮ
	case 0x5:	// ��ɳĮ
	default:
		return cv::imread("pictures/default.png");
	}
}

static cv::Mat getUnknownMatByBase(unsigned int base)
{
	switch (base) {
	case 0x0:	// ˮ��
		return cv::imread("pictures/box/water/unknown.png");
	case 0x1:	// ��ˮ��
	case 0x2:	// ɭ��
	case 0x3:	// ��ɭ��
	case 0x4:	// ɳĮ
	case 0x5:	// ��ɳĮ
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
	// ƽ̹����
	if (isPlain()) {
		return getPlainMatByBase(base);
	}

	// δ֪����
	if (isUnknown()) {
		return getUnknownMatByBase(base);
	}
	
	// ��֪�ķ�ƽ̹����
	switch (base) {
	case 0x0:	// ˮ��
		return getWaterMat(type);
	case 0x1:	// ��ˮ��
		return getDeepWaterMat(type);
	case 0x2:	// ɭ��
		return getForestMat(type);
	case 0x3:	// ��ɭ��
		return getDeepForestMat(type);
	case 0x4:	// ɳĮ
		return getDesertMat(type);
	case 0x5:	// ��ɳĮ
		return getDeepDesertMat(type);
	default:
		break;
	}

	return cv::imread("pictures/default.png");
}

/* �ھ�δ֪���飬ʹ������֪ */
void Box::dig(void)
{
	if (isUnknown()) {
		type++;
	}
	return;
}

/* ��������������Ϊƽ̹ */
void Box::setPlain(void)
{
	type &= 0xF000;
	return;
}
