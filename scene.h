#ifndef _SCENE_H_
#define _SCENE_H_

#include <thread>
#include "role.h"
#include "box.h"
#include "music.h"
#include "bag.h"
#include "scene_load.h"
#include "tools.h"

/* һЩ��������� */
#define WELCOME 0		// ��ӭ����
#define SEEBUTTON 1		// �鿴����
#define SETFPS 2		// ����֡�ʽ���
#define READARCHIVE 3	// ��ȡ�浵
#define GAME 10			// ��Ϸ����

#define ENTER 13	// ��ENTER���õ���ASCII��ֵ
#define ESC 27		// ��ESC���õ���ASCII��ֵ

class Scene {
private:
	unsigned short fps;			// ֡��
	unsigned short width;		// ��ȣ����أ�
	unsigned short height;		// �߶ȣ����أ�
	unsigned int gameWidth;		// ��Ϸ��һ���ߵķ��������������
	unsigned char seeRows;		// ��ʾ����
	unsigned char seeCols;		// ��ʾ����
	unsigned char type;			// ��������
	unsigned char welcomeMode;	// ��ӭ�����ָ��λ��
	unsigned char fpsMode;		// FPSѡ��
	unsigned short state;		// ������״̬
	Role role;					// ����
	cv::Point rolePos;			// ��������λ�ã���ʼ����
	unsigned short roleState;	// ����״̬
	int seed;					// ���Ӻ�
	Box*** boxes;				// �൱�ڶ�ά���飬�洢�����״̬
	Bag bag;					// ����

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