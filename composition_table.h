#ifndef _COMPOSITION_TABLE_H_
#define _COMPOSITION_TABLE_H_

#include <opencv2/opencv.hpp>
#include "bag.h"
#include "scene_load.h"

#define ENTER 13	// ��ENTER���õ���ASCII��ֵ
#define ESC 27		// ��ESC���õ���ASCII��ֵ

#define COMPOSITIONDATA1NUM 7
#define COMPOSITIONDATA2NUM 20

class CompositionTable {
private:
	char state; // 0�������1ѡ���2ѡ����ϳ���
	unsigned char data1; // 0��ʾ��һ��
	unsigned short data2; // 0��ʾ��һ��


public:
	CompositionTable(void);
	~CompositionTable(void);

	void setState(short state);
	short getState(void);
	void setData1(short data1);
	short getData1(void);
	void setData2(short data2);
	short getData2(void);

	bool parseKey(int key, Bag& bag); // �������޹��򷵻�false
	cv::Mat getMat(Bag bag);
};

#endif /* _COMPOSITION_TABLE_H_ */