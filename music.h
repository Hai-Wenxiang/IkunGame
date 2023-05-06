#ifndef _MUSIC_H_
#define _MUSIC_H_

#include <set>
#include <time.h>
#include <string>
#include <random>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#pragma comment(lib,"WinMM.Lib")


#define MAXLEN 255
#define MUSICSTRLEN 8


#define NGM "music/ngm.wav" // ����ﰥӴ
#define JI "music/ji.wav"	// ֻ��


/* ����һ������ */
void playOnce(const char* musicPos, std::set<unsigned long long> musicSet);

/* ѭ���������� */
void playLoop(const char* musicPos);

#endif // _MUSIC_H_