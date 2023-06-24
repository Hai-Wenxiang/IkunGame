#ifndef _COMPOSITION_TABLE_H_
#define _COMPOSITION_TABLE_H_

#include <opencv2/opencv.hpp>
#include "bag.h"
#include "scene_load.h"

#define ENTER 13	// 按ENTER键得到的ASCII码值
#define ESC 27		// 按ESC键得到的ASCII码值

#define COMPOSITIONDATA1NUM 7
#define COMPOSITIONDATA2NUM 20

class CompositionTable {
private:
	char state; // 0不在这里，1选类别，2选具体合成项
	unsigned char data1; // 0表示第一项
	unsigned short data2; // 0表示第一项


public:
	CompositionTable(void);
	~CompositionTable(void);

	void setState(short state);
	short getState(void);
	void setData1(short data1);
	short getData1(void);
	void setData2(short data2);
	short getData2(void);

	bool parseKey(int key, Bag& bag); // 若与其无关则返回false
	cv::Mat getMat(Bag bag);
};

#endif /* _COMPOSITION_TABLE_H_ */