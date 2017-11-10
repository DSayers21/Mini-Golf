#pragma once

#include "MainGame.h"
#include "Window.h"
#include "Input.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Vert.h"
#include "BasicShader.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Transform.h"
#include "Camera.h"
#include "Vector3f.h"
#include <iostream>
#include "MeshRenderer.h"
#include "GameObject.h"

class TestGame : public MainGame
{
public:
	TestGame();
	~TestGame();

	void Init();
	void Input();
	//void Update();

	//Setters

private:
	D3DEngine::PointLight* m_pLights;
	D3DEngine::PointLight* m_PLight1;
	D3DEngine::PointLight* m_PLight2;
	D3DEngine::SpotLight* m_SpotLights;
	float m_Wave = 0.0f;
};

