#include "role.h"

Role::Role(void)
{
	blood = 10000;
	hield.freeRatio = 0;
	hield.remain = 0;
	satiety = 0;
	toward = LEFT;
	state = 0;
	return;
}

Role::~Role(void)
{
	return;
}

void Role::setBlood(short newBlood)
{
	blood = newBlood;
	return;
}

short Role::getBlood(void)
{
	return blood;
}

void Role::setHield(Hield newHield)
{
	hield = newHield;
	return;
}

Hield Role::getHield(void)
{
	return hield;
}

void Role::setSatiety(short newSatiety)
{
	if (newSatiety >= 0 && newSatiety <= 10000) {
		satiety = newSatiety;
	}
	return;
}

short Role::getSatiety(void)
{
	return satiety;
}

void Role::setToward(short newToward)
{
	toward = newToward;
	return;
}

short Role::getToward(void)
{
	return toward;
}

/* 判定角色是否活着 */
bool Role::isAlive(void)
{
	return blood > 0;
}

/* 改变血量 */
void Role::changeBlood(short delta)
{
	blood += delta;
	if (blood < 0) {
		blood = 0;
	}
	else if (blood > 10000) {
		blood = 10000;
	}
	return;
}

static cv::Mat getRoleMat(unsigned short state)
{
	static cv::Mat roleMats[] = {
		cv::imread("pictures/role/role00000.png")
	};

	if (state < sizeof(roleMats) / sizeof(cv::Mat)) {
		return roleMats[state];
	}

	static cv::Mat defaultMat = cv::imread("pictures/default.png");
	return defaultMat;
}

cv::Mat Role::getMat(void)
{
	cv::Mat roleMat = getRoleMat(state).clone();
	switch (toward) {
	case 1:
	case 3:
		cv::rotate(roleMat, roleMat, toward - 1);
		break;
	case 2:
		cv::flip(roleMat, roleMat, 1);
		break;
	default:
		break;
	}
	return roleMat;
}
