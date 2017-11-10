#pragma once

#include "Window.h"
#include "Input.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Vert.h"
#include "PhongShader.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Transform.h"
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
	D3DEngine::Mesh* m_Mesh;
	D3DEngine::PhongShader m_BShader;
	D3DEngine::Transform m_Transform;
	D3DEngine::Camera* m_Camera;
	//D3DEngine::Texture* m_Texture;
	D3DEngine::Material* m_Material;

	D3DEngine::PointLight* m_pLights;
	D3DEngine::PointLight* m_PLight1;
	D3DEngine::PointLight* m_PLight2;
	D3DEngine::SpotLight* m_SpotLights;
	float m_Wave = 0.0f;
};