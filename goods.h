#ifndef _GOODS_H_
#define _GOODS_H_

#include "goods_load.h"

#define MAXGOODSNUM 114514	// 物品最大数量

/**
 * 背包中的物品
 *
 * type = 0 表示空
 *
 * type = 1 表示木头01
 * state = 0 表示木头状态
 * state = 1 表示木板状态
 *
 * type = 2 表示
 */
class Goods {
private:
	unsigned int type;	// 种类
	unsigned int state;	// 状态
	unsigned int num;	// 数量

public:
	Goods(void);
	~Goods(void);

	void setType(unsigned int newType);
	unsigned int getType(void);
	void setState(unsigned int newState);
	unsigned int getState(void);
	void setNum(unsigned int newNum);
	unsigned int getNum(void);

	bool equals(Goods goods);
	bool add(unsigned int add);
	bool sub(unsigned int sub);
	cv::Mat getMat(void);
};

#endif // _GOODS_H_