#pragma once

//Includes
#include <iostream>
#include <string>

#include "Window.h"
#include "Input.h"
#include "GameObject.h"
#include "RenderEngine.h"
#include "PhysicsEngine.h"
#include "ResourceManagement/MeshList.h"

//Forward declaration
class MainComp;

class MainGame
{
public:
	//Constructor
	MainGame();
	//Virtual Destructor
	virtual ~MainGame();

	//Virtual functions (to be overwritten by child classes)
	virtual void Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine);
	virtual void Input(D3DEngine::GetInput* input, float Delta);
	virtual void Update(float Delta);
	virtual void Draw(D3DEngine::RenderEngine* renderEngine);

	//Function to add object
	void AddObject(D3DEngine::GameObject* obj) { GetRootObject()->AddChild(obj); }

	//Setters
	virtual inline void SetTime(D3DEngine::Time* time) { m_Time = time; }
	virtual void SetWindow(D3DEngine::Window* Window);
	void SetEngine(D3DEngine::MainComp * mainComp);

protected:
	//Getters
	inline D3DEngine::GameObject* GetRootObject() { return m_RootObject; }

	//Pointer to window
	D3DEngine::Window* m_Window;
	//Pointer to time
	D3DEngine::Time* m_Time;
	//Pointer to the root object
	D3DEngine::GameObject* m_RootObject;
	//Pointer to the mesh list
	D3DEngine::MeshList* m_MeshList = new D3DEngine::MeshList();
};