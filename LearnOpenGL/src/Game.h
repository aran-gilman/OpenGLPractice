#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Window.h"

struct GameData;

class Game : IWindowListener
{
public:
	Game();
	~Game();

	void OnUpdate(Window* window, double elapsedTime) override;
	void OnResize(int width, int height) override;
	void OnKeyInput(int keyToken, int scancode, int action, int mods) override;
	void OnMousePosition(double x, double y, double xOffset, double yOffset);

	void Run();

private:
	Window window;
	std::unique_ptr<GameData> gameData;
};

#endif
