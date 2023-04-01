#include "music.h"

void playOnce(const char* musicPos)
{
	WCHAR text[MAXLEN] = { 0 };
	swprintf(text, MAXLEN, L"%hs%hs", "play ", musicPos);
	mciSendString(text, NULL, 0, NULL);
	return;
}

void playLoop(const char* musicPos)
{
	while (true) {
		playOnce(musicPos);
	}
}
