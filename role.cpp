#include "role.h"

Role::Role()
{
	blood = 100.0;
	hield.freeRatio = 0.0;
	hield.remain = 0.0;
	satiety = 0.0;
	toward = LEFT;
	return;
}

Role::~Role(void)
{
	return;
}

void Role::setBlood(double newBlood)
{
	blood = newBlood;
	return;
}

double Role::getBlood(void)
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

void Role::setSatiety(double newSatiety)
{
	if (newSatiety >= 0.0 && newSatiety <= 100.0) {
		satiety = newSatiety;
	}
	return;
}

double Role::getSatiety(void)
{
	return satiety;
}

void Role::setToward(unsigned char newToward)
{
	toward = newToward;
	return;
}

unsigned char Role::getToward(void)
{
	return toward;
}

/* 判定角色是否活着 */
bool Role::isAlive(void)
{
	return blood > 0.0;
}

/* 改变血量 */
void Role::changeBlood(double delta)
{
	blood += delta;
	if (blood < 0.0) {
		blood = 0.0;
	}
	else if (blood > 100.0) {
		blood = 100.0;
	}
	return;
}

cv::Mat Role::getMat(void)
{
	cv::Mat roleMat =  cv::imread("pictures/role/role00000.png");
	if (toward > 0) {
		cv::rotate(roleMat, roleMat, toward - 1);
	}
	return roleMat;
}
