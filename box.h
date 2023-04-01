#pragma once
#include <Windows.h>
#include <opencv2/opencv.hpp>

#define BOXWIDTH 60	// 每个方块边长为60

/**
 * 用于记录方块种类的unsigned short类型
 * 
 * 高4位用于表示所属种群
 * 
 * 低12位用于表示具体种类
 * 其中，最低位为0表示已知，最低位为1表示未知
 * 除平坦外，其余内容：奇数表示未知，奇数 + 1表示已知
 */
/* 水域 */
#define WATER_PLAIN 0x0000				// 平坦
#define WATER_UNKNOWN_ICE 0x0001		// 未知的冰块
#define WATER_ICE 0x0002				// 已知的冰块
#define WATER_UNKNOWN_WOOD_01 0x0003	// 未知的木头01
#define WATER_WOOD_01 0x0004			// 已知的木头01
/* 深水域 */
#define DEEP_WATER_PLAIN 0x1000				// 平坦
#define DEEP_WATER_UNKNOWN_ICE 0x1001		// 未知的冰块
#define DEEP_WATER_ICE 0x1002				// 已知的冰块
/* 森林 */
#define FOREST_PLAIN 0x2000				// 平坦
#define FOREST_UNKNOWN_WOOD_01 0x2001	// 未知的木头01
#define FOREST_WOOD_01 0x2002			// 已知的木头01
#define FOREST_UNKNOWN_WOOD_02 0x2003	// 未知的木头02
#define FOREST_WOOD_02 0x2004			// 已知的木头02
/* 深森林 */
#define DEEP_FOREST_PLAIN 0x3000			// 平坦
#define DEEP_FOREST_UNKNOWN_WOOD_01 0x3001	// 未知的木头01
#define DEEP_FOREST_WOOD_01 0x3002			// 未知的木头01
#define DEEP_FOREST_UNKNOWN_WOOD_02 0x3003	// 未知的木头02
#define DEEP_FOREST_WOOD_02 0x3004			// 未知的木头02
/* 沙漠 */
#define DESERT_PLAIN 0x4000				// 平坦
/* 深沙漠 */
#define DEEP_DESERT_PLAIN 0x5000			// 平坦

class Box {
private:
	unsigned short type;		// 方块的种类
	unsigned short state;		// 方块的状态
	ULONGLONG stateStartTime;	// 方块状态初始时间


public:
	Box(unsigned short newType);
	~Box(void);

	void setType(unsigned short newType);
	unsigned short getType(void);
	void setState(unsigned short newState);
	unsigned short getState(void);
	void setStateStartTime(void);
	ULONGLONG getStateStartTime(void);

	unsigned char getBase(void);
	bool isPlain(void);
	bool isUnknown(void);
	bool canFetch(void);
	cv::Mat getMat(void);
	void dig(void);
	void setPlain(void);
};