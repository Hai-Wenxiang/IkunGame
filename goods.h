#ifndef _GOODS_H_
#define _GOODS_H_

#include "goods_load.h"

#define MAXGOODSNUM 114514	// ��Ʒ�������

/**
 * �����е���Ʒ
 *
 * type = 0 ��ʾ��
 *
 * type = 1 ��ʾľͷ01
 * state = 0 ��ʾľͷ״̬
 * state = 1 ��ʾľ��״̬
 *
 * type = 2 ��ʾ
 */
class Goods {
private:
	unsigned int type;	// ����
	unsigned int state;	// ״̬
	unsigned int num;	// ����

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