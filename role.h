#ifndef _ROLE_H_
#define _ROLE_H_

#include <opencv2/opencv.hpp>

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

/* �������ͽṹ�� */
typedef struct hieldStruct {
	short freeRatio;	// [0 , 10000) * 0.01���������˱���
	short remain;		// ÿ100����1���ٷֵ㣬ʣ���� [0, 10000] * 0.01
} Hield;

class Role {
private:
	short blood;					// [0 ~ 10000]Ѫ��������Ϊ10000��0ʱ����
	Hield hield;					// ����
	unsigned short satiety : 14;	// �����ȣ�[0, 10000] * 0.01�����ܳ�
	unsigned short toward : 2;		// ����0�� 1�� 2�� 3��
	unsigned short state;			// ��ɫ��״̬


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