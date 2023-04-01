#ifndef _ROLE_H_
#define _ROLE_H_

#include <opencv2/opencv.hpp>

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

/* 护盾类型结构体 */
typedef struct hieldStruct {
	short freeRatio;	// [0 , 10000) * 0.01，代表免伤比例
	short remain;		// 每100代表1个百分点，剩余量 [0, 10000] * 0.01
} Hield;

class Role {
private:
	short blood;					// [0 ~ 10000]血量，上限为10000，0时死亡
	Hield hield;					// 护盾
	unsigned short satiety : 14;	// 饱腹度，[0, 10000] * 0.01，不能撑
	unsigned short toward : 2;		// 朝向，0左 1上 2右 3下
	unsigned short state;			// 角色的状态


public:
	Role(void);
	~Role(void);

	void setBlood(short newBlood);
	short getBlood(void);
	void setHield(Hield newHield);
	Hield getHield(void);
	void setSatiety(short newSatiety);
	short getSatiety(void);
	void setToward(short newToward);
	short getToward(void);

	bool isAlive(void);
	void changeBlood(short delta);
	cv::Mat getMat(void);
};

#endif // _ROLE_H_