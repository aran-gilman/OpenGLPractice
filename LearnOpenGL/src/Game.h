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

	Window* GetWindow() { return &window; }

	Event<double>& OnUpdate() { return onUpdate; }
	Event<double>& OnRender() { return onRender; }

	void Run();

private:
	Window window;
	std::unique_ptr<GameData> gameData;

	Event<double> onUpdate;
	Event<double> onRender;

	void HandleUpdate(double elapsedTime);
	void HandleKeyInput(int keyToken, int scancode, int action, int mods);
};

#endif
