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
#include "GameObject.h"
#include "Vector3f.h"
#include <iostream>

class MainGame
{
public:
	MainGame();
	~MainGame();

	virtual void Init();
	virtual void Input();
	virtual void Update();
	virtual void Draw();
	//Getters
	inline D3DEngine::GameObject* GetRootObject() { return m_RootObject; }
	//Setters
	virtual inline void SetTime(D3DEngine::Time* time) { m_Time = time; }
	virtual void SetWindow(D3DEngine::Window* Window);

protected:
	D3DEngine::Window* m_Window;
	D3DEngine::Time* m_Time;
	D3DEngine::Input* m_Input;
	D3DEngine::Camera* m_Camera;
	D3DEngine::GameObject* m_RootObject;
};