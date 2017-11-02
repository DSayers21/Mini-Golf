#pragma once

#include <Camera.h>

class MainGame
{
public:
	MainGame();
	~MainGame();

	void RenderScene(void);
	void SpecKeyboardFunc(int key, int x, int y);
	void SpecKeyboardUpFunc(int key, int x, int y);
	void KeyboardFunc(unsigned char key, int x, int y);
	void KeyboardUpFunc(unsigned char key, int x, int y);
	void ChangeSize(int w, int h);

	void UpdateScene(int ms);
private:
	Camera TestCamera;
};

