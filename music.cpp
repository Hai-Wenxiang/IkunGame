#include "music.h"

unsigned long long getMusicStrData(char* str)
{
	unsigned long long data = 0;
	for (int i = 0; i < MUSICSTRLEN; i++) {
		data |= (unsigned long long)(str[i] - 'a') << (i * 5);
	}
	return data;
}

char* getMusicStr(std::set<unsigned long long> musicSet, std::random_device& randSeed)
{
	unsigned long long data = 0;

	char* p = (char*)malloc(sizeof(char) * (MUSICSTRLEN + 1));
	while (p == NULL) {
		p = (char*)malloc(sizeof(char) * (MUSICSTRLEN + 1));
	}
	while (data == (unsigned long long)0) {
		for (int i = 0; i < MUSICSTRLEN; i++) {
			p[i] = randSeed() % 26 + 'a';
		}
		data = getMusicStrData(p);
		if (musicSet.find(data) == musicSet.end()) {
			musicSet.insert(data);
			break;
		}
		data = (unsigned long long)0;
	}
	p[MUSICSTRLEN] = 0;
	return p;
}

void playOnce(const char* musicPos, std::set<unsigned long long> musicSet)
{
	std::random_device randSeed;
	WCHAR text[MAXLEN] = { 0 };
	char* musicStr = getMusicStr(musicSet, randSeed);
	swprintf(text, MAXLEN, L"%hs%hs%hs%hs", "open ", musicPos, " alias ", musicStr);
	std::cout << musicStr << std::endl;
	mciSendString(text, NULL, 0, NULL);
	swprintf(text, MAXLEN, L"%hs%hs", "play ", musicStr);
	mciSendString(text, NULL, 0, NULL);
	musicSet.erase(getMusicStrData(musicStr));
	free(musicStr);
	return;
}

void playLoop(const char* musicPos)
{
	WCHAR text[MAXLEN] = { 0 };
	swprintf(text, MAXLEN, L"%hs%hs", "play ", musicPos);
	while (true) {
		mciSendString(text, NULL, 0, NULL);
	}
}
