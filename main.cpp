#pragma once
#include <thread>
#include "scene.h"
#include "music.h"
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )

int main()
{
	cv::Mat img;
	std::thread music(playLoop, NGM);
	Scene scene = Scene();
	ULONGLONG startTime, remainTime;
	std::cout << "Box ------- > " << sizeof(Box) << '\t' << sizeof(Scene) << std::endl;

	music.detach();
	srand(time(NULL));
	for (int key = -1; scene.notExitGame(key); key = cv::waitKey(remainTime)) {
		startTime = GetTickCount64();
		scene.parse(key);
		img = scene.getMat();
		remainTime = 1000 / scene.getFps() - (GetTickCount64() - startTime);
		cv::imshow("Game", img);
	}
	return 0;
}