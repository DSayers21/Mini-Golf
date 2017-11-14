#pragma once

#include "Window.h"
#include "Input.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Vert.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Transform.h"
#include "Camera.h"
#include "GameObject.h"
#include "Vector3f.h"
#include <iostream>
#include <string>
#include "RenderEngine.h"

class MainGame
{
public:
	MainGame();
	~MainGame();

	virtual void Init();
	virtual void Input(D3DEngine::GetInput* input, float Delta);
	virtual void Update(float Delta);
	virtual void Draw(D3DEngine::RenderEngine* renderEngine);

	void AddObject(D3DEngine::GameObject* obj) { GetRootObject()->AddChild(obj); }

	//Setters
	virtual inline void SetTime(D3DEngine::Time* time) { m_Time = time; }
	virtual void SetWindow(D3DEngine::Window* Window);
protected:
	//Getters
	inline D3DEngine::GameObject* GetRootObject() { return m_RootObject; }

	D3DEngine::Window* m_Window;
	D3DEngine::Time* m_Time;
	D3DEngine::GameObject* m_RootObject;
};