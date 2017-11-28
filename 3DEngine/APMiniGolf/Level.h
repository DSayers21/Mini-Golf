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
#include <map>
#include <string> 

enum TYPE{
	BALL,
	WALLBACK,
	WALLSIDE
};

//Change to bitflagging if works
struct Tile {
	Tile() {}

	bool Top = false;
	bool Bottom = false;
	bool Right = false;
	bool Left = false;
};

struct LevelID {
	LevelID(int i, int j, int pos, D3DEngine::Vector3f tileCenter, TYPE type) {
		I = i; J = j; Pos = pos; TileCenter = tileCenter; m_Type = type;
	}
	
	int I;
	int J;
	int Pos;
	D3DEngine::Vector3f TileCenter;

	TYPE m_Type;

};


class Level
{
public:
	void TranslateHelper(float x, float z, int CurCount, D3DEngine::Vector3f tileCenter, D3DEngine::PhysicsEngineComponent * PhysicsEngineComponent);

	void CreateHelper(int CurCount, D3DEngine::Mesh * mesh, D3DEngine::Material * material, D3DEngine::PhysicsEngineComponent * PhysicsEngineComponent, D3DEngine::GameObject * RootObject);

	//9 across by 7 long
	Level(int LevelData[7][7],
		D3DEngine::Window* Window, D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine,
		D3DEngine::GameObject* RootObject);
	Level(D3DEngine::Window * Window, D3DEngine::RenderEngine * renderEngine, D3DEngine::PhysicsEngine * physicsEngine, D3DEngine::GameObject * RootObject);
	~Level();

private:
	D3DEngine::MeshList* m_MeshList = new D3DEngine::MeshList();
	std::vector<D3DEngine::GameObject*> m_GameObjects = std::vector<D3DEngine::GameObject*>();

	std::vector<LevelID> m_ObjectsMap = std::vector<LevelID>();
	std::map<std::string, Tile> m_TileMap = std::map<std::string, Tile>();
};