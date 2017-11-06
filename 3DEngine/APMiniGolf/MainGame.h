#pragma once

#include "Window.h"
#include "Input.h"
#include "Mesh.h"
#include "Vert.h"
#include "Shader.h"
#include "Transform.h"
#include "ResourceLoader.h"
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
	D3DEngine::Mesh* m_Mesh;
	D3DEngine::Shader m_Shader;
	D3DEngine::Transform m_Transform;

	float Temp = 0.0f;
};