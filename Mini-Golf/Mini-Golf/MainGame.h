#pragma once

#include <Lighting.h>
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

	void UpdateScene(int ms);

	//Getters
	D3DEngine::Camera* GetCamera() { return &m_MainCamera; }
private:
	D3DEngine::Camera m_MainCamera;
	D3DEngine::Lighting m_Lighting;
};

