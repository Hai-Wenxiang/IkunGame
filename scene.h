#ifndef _SCENE_H_
#define _SCENE_H_

#include <thread>
#include "role.h"
#include "box.h"
#include "music.h"
#include "bag.h"
#include "scene_load.h"
#include "tools.h"

/* 一些界面的种类 */
#define WELCOME 0		// 欢迎界面
#define SEEBUTTON 1		// 查看按键
#define SETFPS 2		// 设置帧率界面
#define READARCHIVE 3	// 读取存档
#define GAME 10			// 游戏界面

#define ENTER 13	// 按ENTER键得到的ASCII码值
#define ESC 27		// 按ESC键得到的ASCII码值

class Scene {
private:
	unsigned short fps;			// 帧率
	unsigned short width;		// 宽度（像素）
	unsigned short height;		// 高度（像素）
	unsigned int gameWidth;		// 游戏中一条边的方块个数（奇数）
	unsigned char seeRows;		// 显示行数
	unsigned char seeCols;		// 显示列数
	unsigned char type;			// 场景种类
	unsigned char welcomeMode;	// 欢迎界面的指针位置
	unsigned char fpsMode;		// FPS选项
	unsigned short state;		// 场景的状态
	Role role;					// 主角
	cv::Point rolePos;			// 主角所在位置，初始居中
	unsigned short roleState;	// 主角状态
	int seed;					// 种子号
	Box*** boxes;				// 相当于二维数组，存储方块的状态
	Bag bag;					// 背包

	void parseKeyInWelcome(int key);
	void parseKeyInSetFPS(int key);
	void saveGame(void);
	void move(int key);
	Box* getTowardBox(void);
	void dig(void);
	bool canFetch(Box box);
	void fetch(void);
	void exitGame(void);
	void parseKeyInGame(int key);
	void parseKey(int key, std::set<unsigned long long> musicSet);
	void parseScene(void);
	cv::Mat getMatInWelcome(void);
	cv::Mat getMatInSetFPS(void);
	void addMap(cv::Mat mat);
	void addState(cv::Mat mat);
	cv::Mat getMatInGame(void);


public:
	Scene(void);
	~Scene(void);

	void setFps(unsigned short newFps);
	unsigned short getFps(void);
	void setWidth(unsigned short newWidth);
	unsigned short getWidth(void);
	void setHeight(unsigned short newHeight);
	unsigned short getHeight(void);
	void setType(unsigned char newType);
	unsigned char getType(void);
	void setRolePos(cv::Point newPos);
	cv::Point getRolePos(void);
	Box*** getBoxes(void);

	bool notExitGame(int key);
	void parse(int key, std::set<unsigned long long> musicSet);
	cv::Mat getMat(void);
};

#endif // _SCENE_H_