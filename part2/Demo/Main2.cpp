
#include "main.h"

void onApplicationStart(OperatingSystem * operatingSystem) {
    const auto window = &operatingSystem->aquireWindow();
	window->setPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	window->setTitle("AGP Part 2 - B00235610 - 49 Dynamic Point Lights 100+ FPS");
	window->setSize(1050, 650);
	window->create();

	const auto scenes = operatingSystem->aquireSceneManager();
	scenes->packSceneList({  new Menu(operatingSystem), new Level(operatingSystem) });
	operatingSystem->executeProgram();
}