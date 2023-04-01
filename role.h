#pragma once
#include <opencv2/opencv.hpp>

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

/* 护盾类型结构体 */
typedef struct hieldStruct {
	double freeRatio;	// 免伤比例 [0.0, 100.0)
	double remain;		// 剩余量 [0.0, 100.0]
} Hield;

class Role {
private:
	double blood;			// 血量，上限为100，0时死亡
	Hield hield;			// 护盾
	double satiety;			// 饱腹度，[0.0, 100.0]，不能撑
	unsigned char toward;	// 朝向，0坐1上2右3下


public:
	Role();
	~Role(void);

	void setBlood(double newBlood);
	double getBlood(void);
	void setHield(Hield newHield);
	Hield getHield(void);
	void setSatiety(double newSatiety);
	double getSatiety(void);
	void setToward(unsigned char newToward);
	unsigned char getToward(void);

	bool isAlive(void);
	void changeBlood(double delta);
	cv::Mat getMat(void);
};