#pragma once

#include "MainGame.h"
#include "Level.h"

struct LevelArray
{
	int m_LevelData[7][7] = {
		{ 0, 0, 0, 0, 0, 0, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 0
		{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 1
		{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 2
		{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 3
		{ 0, 0, 0, 0, 0, 0, 0 } ,   //Row 4
		{ 0, 0, 0, 0, 0, 0, 0 } ,
	};

	void LevelArray::SetLevelData(int LevelData[7][7])
	{
		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 7; j++)
				m_LevelData[i][j] = LevelData[i][j];
	}
};


class MiniGolf : public MainGame
{
public:
	MiniGolf();
	//~MiniGolf();

	void Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine);
	void Input(D3DEngine::GetInput* input, float Delta);

	bool LoadLevel(int LevelNum);
	void ResetLevel();

private:
	Level* m_CurrentLevel;
	D3DEngine::RenderEngine* m_RenderEngine;
	D3DEngine::PhysicsEngine* m_PhysicsEngine;
};