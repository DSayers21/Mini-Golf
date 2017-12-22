#pragma once

//Includes
#include "RenderEngine.h"
#include "PhysicsEngine.h"
#include "GameObject.h"
#include "PhysicsEngineComponent.h"
#include "PhysicsObjectComponent.h"
#include "Player.h"
#include "Pocket.h"
#include "FreeLook.h"
#include "MeshRenderer.h"
#include "GolfClub.h"
//Lights
#include "DirectionalLight.h"
#include "PointLight.h"
//End Lights
#include <vector>
#include <map>
#include <string> 

//Type enum, for physics objects
enum TYPE{
	BALL,
	WALLBACKF,
	WALLBACKB,
	WALLSIDEL,
	WALLSIDER
};

//Tile struct to remember which walls a tile has
struct Tile 
{
	//Empty Constructor
	Tile() {}
	//Bool flags to remember which directions have walls
	bool Top = false;
	bool Bottom = false;
	bool Right = false;
	bool Left = false;
};

//LevelID struct
struct LevelID 
{
	//Constructor
	LevelID(int i, int j, int pos, D3DEngine::Vector3f tileCenter, TYPE type) :
		I(i), J(j), Pos(pos), TileCenter(tileCenter), m_Type(type)
	{
		//empty
	}
	//I, J and position created
	int I, J, Pos;
	//Center of tile
	D3DEngine::Vector3f TileCenter;
	//The type of object e.g. ball, wall etc
	TYPE m_Type;
};

class Level
{
public:
	//Helper function to translate the physics objects to where they should be
	void TranslateHelper(float x, float z, int CurCount, D3DEngine::Vector3f tileCenter, D3DEngine::PhysicsEngineComponent * PhysicsEngineComponent);
	//Helper function to create the physics objects
	void CreateHelper(int CurCount, D3DEngine::Mesh * mesh, D3DEngine::Material * material, D3DEngine::PhysicsEngineComponent * PhysicsEngineComponent, D3DEngine::GameObject * RootObject);

	//Constructor
	Level(int NumOfPlayers, int LevelData[7][7],
		D3DEngine::Window* Window, D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine,
		D3DEngine::GameObject* RootObject);
	//Destructor
	~Level();
	
	//Function to dispose of current level
	void Destroy();
	//Function to reset ball back to original position
	void ResetBall();
	//Update function
	bool Update(float Delta);

	//Getters
	inline std::vector<Player*> GetPlayers() { return m_Players; }

private:
	//Bool to track if current player has putted the ball
	bool m_Finished = false;
	//Current player
	int m_CurrentPlayer = 0;
	//Pocket object
	Pocket* m_Pocket;
	//List of players
	std::vector<Player*> m_Players;

	//Mesh List
	D3DEngine::MeshList m_MeshList = D3DEngine::MeshList();
	//Mateiral List
	std::vector<D3DEngine::Material*> m_MaterialList = std::vector<D3DEngine::Material*>();
	//Physics Component
	D3DEngine::PhysicsEngineComponent* m_PhysicsEngineComponent;

	//Objects and Tile map, for use when level being created
	std::vector<LevelID> m_ObjectsMap = std::vector<LevelID>();
	std::map<std::string, Tile> m_TileMap = std::map<std::string, Tile>();
};