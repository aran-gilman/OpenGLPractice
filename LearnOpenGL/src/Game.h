#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Window.h"

struct GameData;

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	Window window;
	std::unique_ptr<GameData> gameData;

	void OnUpdate(double elapsedTime);
	void OnKeyInput(int keyToken, int scancode, int action, int mods);
};

#endif
