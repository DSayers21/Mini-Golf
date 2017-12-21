#pragma once

#include "MainGame.h"
#include "Level.h"
#include "GolfCourse.h"

class MiniGolf : public MainGame
{
public:
	MiniGolf();
	virtual ~MiniGolf();

	void Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine);
	void Input(D3DEngine::GetInput* input, float Delta);
	virtual void Update(float Delta);

	bool LoadLevel(int LevelNum);
	void ResetLevel();

private:
	int m_MoveToNextLevel = -2;
	bool LevelEmpty = true;
	GolfCourse m_Course;
	Level* m_CurrentLevel;

	int m_NumOfPlayers = 4;

	D3DEngine::RenderEngine* m_RenderEngine;
	D3DEngine::PhysicsEngine* m_PhysicsEngine;
};