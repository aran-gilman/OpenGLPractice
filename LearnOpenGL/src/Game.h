#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Window.h"

class Game : IWindowListener
{
public:
	Game();

	void OnUpdate(Window* window, double elapsedTime) override;
	void OnResize(int width, int height) override;
	void OnKeyInput(int keyToken, int scancode, int action, int mods) override;
	void OnMousePosition(double x, double y, double xOffset, double yOffset);

	void Run();

private:
	Window window;

	Material material;
	Mesh mesh;
	Camera camera;

	std::vector<Transform> meshTransforms;
};

#endif
