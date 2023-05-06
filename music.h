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


#define NGM "music/ngm.wav" // 你干嘛哎哟
#define JI "music/ji.wav"	// 只因


/* 播放一次音乐 */
void playOnce(const char* musicPos, std::set<unsigned long long> musicSet);

/* 循环播放音乐 */
void playLoop(const char* musicPos);

#endif // _MUSIC_H_