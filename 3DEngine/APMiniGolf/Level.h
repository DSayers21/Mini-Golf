#pragma once
#include "RenderEngine.h"
#include "PhysicsEngine.h"
#include "GameObject.h"
#include "PhysicsEngineComponent.h"
#include "PhysicsObjectComponent.h"

#include "FreeLook.h"
#include "MeshRenderer.h"
#include "GolfClub.h"
#include "DirectionalLight.h"
#include <vector>

class Level
{
public:
	//9 across by 7 long
	Level(int LevelData[5][5],
		D3DEngine::Window* Window, D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine,
		D3DEngine::GameObject* RootObject);
	Level(D3DEngine::Window * Window, D3DEngine::RenderEngine * renderEngine, D3DEngine::PhysicsEngine * physicsEngine, D3DEngine::GameObject * RootObject);
	~Level();

private:
	D3DEngine::MeshList* m_MeshList = new D3DEngine::MeshList();
	std::vector<D3DEngine::GameObject*> m_GameObjects = std::vector<D3DEngine::GameObject*>();
};

