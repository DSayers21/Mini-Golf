#pragma once

#include "Window.h"
#include "Input.h"
#include "Mesh.h"
#include "Vert.h"
#include <iostream>

class MainGame
{
public:
	MainGame(D3DEngine::Window* window);
	~MainGame();

	void Input();
	void Update();
	void Draw();
private:
	D3DEngine::Window* m_Window;
	D3DEngine::Input* m_Input;
	D3DEngine::Mesh m_Mesh;
};