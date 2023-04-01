#pragma once
#include <opencv2/opencv.hpp>

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

/* �������ͽṹ�� */
typedef struct hieldStruct {
	double freeRatio;	// ���˱��� [0.0, 100.0)
	double remain;		// ʣ���� [0.0, 100.0]
} Hield;

class Role {
private:
	double blood;			// Ѫ��������Ϊ100��0ʱ����
	Hield hield;			// ����
	double satiety;			// �����ȣ�[0.0, 100.0]�����ܳ�
	unsigned char toward;	// ����0��1��2��3��


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