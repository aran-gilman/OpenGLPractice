#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Window.h"

class Camera;
struct GameData;
class Object;

class Game
{
public:
	Game();
	~Game();

	Window* GetWindow() { return &window; }

	Event<double>& OnUpdate() { return onUpdate; }
	Event<double>& OnRender() { return onRender; }

	void Run();

	void RegisterCamera(Camera* camera);
	void UnregisterCamera(Camera* camera);

private:
	Window window;
	std::vector<Camera*> cameras;

	std::vector<std::unique_ptr<Object>> objects;

	std::unique_ptr<GameData> gameData;

	Event<double> onUpdate;
	Event<double> onRender;

	void HandleUpdate(double elapsedTime);
	void HandleKeyInput(int keyToken, int scancode, int action, int mods);
};

#endif
