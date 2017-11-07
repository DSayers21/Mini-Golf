#pragma once

#include "Window.h"
#include "Input.h"
#include "Mesh.h"
#include "Texture.h"
#include "Vert.h"
#include "Shader.h"
#include "Transform.h"
#include "ResourceLoader.h"
#include "Camera.h"
#include "Vector3f.h"
#include <iostream>

class MainGame
{
public:
	MainGame(D3DEngine::Window* window, D3DEngine::Time* time);
	~MainGame();

	void Input();
	void Update();
	void Draw();
private:
	D3DEngine::Window* m_Window;
	D3DEngine::Time* m_Time;
	D3DEngine::Input* m_Input;
	D3DEngine::Mesh m_Mesh;
	D3DEngine::Shader m_Shader;
	D3DEngine::Transform m_Transform;
	D3DEngine::Camera m_Camera;
	D3DEngine::Texture* m_Texture;
	float Temp = 0.0f;
};