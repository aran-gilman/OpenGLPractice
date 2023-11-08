#ifndef GAME_H
#define GAME_H

#include <vector>

#include "ShaderBufferManager.h"
#include "Window.h"

class AmbientLight;
class Camera;
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

	Object* CreateObject();

	void RegisterCamera(Camera* camera);
	void UnregisterCamera(Camera* camera);

private:
	Window window;
	Event<double> onUpdate;
	Event<double> onRender;

	ShaderBufferManager cameraBuffer;
	ShaderBufferManager ambientLightBuffer;
	ShaderBufferManager directionalLightBuffer;

	std::vector<Camera*> cameras;
	std::vector<std::unique_ptr<Object>> objects;

	void HandleUpdate(double elapsedTime);
	void HandleKeyInput(int keyToken, int scancode, int action, int mods);
};

#endif
