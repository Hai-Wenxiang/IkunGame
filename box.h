#pragma once
#include <Windows.h>
#include <opencv2/opencv.hpp>

#define BOXWIDTH 60	// ÿ������߳�Ϊ60

/**
 * ���ڼ�¼���������unsigned short����
 * 
 * ��4λ���ڱ�ʾ������Ⱥ
 * 
 * ��12λ���ڱ�ʾ��������
 * ���У����λΪ0��ʾ��֪�����λΪ1��ʾδ֪
 * ��ƽ̹�⣬�������ݣ�������ʾδ֪������ + 1��ʾ��֪
 */
/* ˮ�� */
#define WATER_PLAIN 0x0000				// ƽ̹
#define WATER_UNKNOWN_ICE 0x0001		// δ֪�ı���
#define WATER_ICE 0x0002				// ��֪�ı���
#define WATER_UNKNOWN_WOOD_01 0x0003	// δ֪��ľͷ01
#define WATER_WOOD_01 0x0004			// ��֪��ľͷ01
/* ��ˮ�� */
#define DEEP_WATER_PLAIN 0x1000				// ƽ̹
#define DEEP_WATER_UNKNOWN_ICE 0x1001		// δ֪�ı���
#define DEEP_WATER_ICE 0x1002				// ��֪�ı���
/* ɭ�� */
#define FOREST_PLAIN 0x2000				// ƽ̹
#define FOREST_UNKNOWN_WOOD_01 0x2001	// δ֪��ľͷ01
#define FOREST_WOOD_01 0x2002			// ��֪��ľͷ01
#define FOREST_UNKNOWN_WOOD_02 0x2003	// δ֪��ľͷ02
#define FOREST_WOOD_02 0x2004			// ��֪��ľͷ02
/* ��ɭ�� */
#define DEEP_FOREST_PLAIN 0x3000			// ƽ̹
#define DEEP_FOREST_UNKNOWN_WOOD_01 0x3001	// δ֪��ľͷ01
#define DEEP_FOREST_WOOD_01 0x3002			// δ֪��ľͷ01
#define DEEP_FOREST_UNKNOWN_WOOD_02 0x3003	// δ֪��ľͷ02
#define DEEP_FOREST_WOOD_02 0x3004			// δ֪��ľͷ02
/* ɳĮ */
#define DESERT_PLAIN 0x4000				// ƽ̹
/* ��ɳĮ */
#define DEEP_DESERT_PLAIN 0x5000			// ƽ̹

class Box {
private:
	unsigned short type;		// ���������
	unsigned short state;		// �����״̬
	ULONGLONG stateStartTime;	// ����״̬��ʼʱ��


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