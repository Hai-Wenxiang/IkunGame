#ifndef _MUSIC_H_
#define _MUSIC_H_

#include <string>
#include <Windows.h>
#pragma comment(lib,"WinMM.Lib")

#define MAXLEN 255

#define NGM "music/ngm.wav" // 你干嘛哎哟
#define JI "music/ji.wav"	// 只因

/* 播放一次音乐 */
void playOnce(const char* musicPos);

/* 循环播放音乐 */
void playLoop(const char* musicPos);

#endif // _MUSIC_H_