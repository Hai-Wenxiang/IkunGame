#ifndef _MUSIC_H_
#define _MUSIC_H_

#include <string>
#include <Windows.h>
#pragma comment(lib,"WinMM.Lib")

#define MAXLEN 255

#define NGM "music/ngm.wav" // ����ﰥӴ
#define JI "music/ji.wav"	// ֻ��

/* ����һ������ */
void playOnce(const char* musicPos);

/* ѭ���������� */
void playLoop(const char* musicPos);

#endif // _MUSIC_H_