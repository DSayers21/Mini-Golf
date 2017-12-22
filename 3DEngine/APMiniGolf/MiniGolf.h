#pragma once

#include "MainGame.h"
#include "Level.h"
#include "GolfCourse.h"
#include "Menu.h"

class MiniGolf : public MainGame
{
public:
	MiniGolf();
	virtual ~MiniGolf();

	void Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine);
	void Input(D3DEngine::GetInput* input, float Delta);
	void Update(float Delta);
	void Draw(D3DEngine::RenderEngine* renderEngine);

	bool LoadLevel(int LevelNum);
	void ResetLevel();

private:
	bool m_Menu = true;
	bool m_CourseFinished = false;
	int m_MoveToNextLevel = -2;
	bool LevelEmpty = true;
	GolfCourse m_Course;
	Level* m_CurrentLevel;

	Rectangle m_OnePlayer;
	Rectangle m_TwoPlayer;
	Rectangle m_FourPlayer;
	Rectangle m_StartGame;

	int m_NumOfPlayers = 4;


	int* m_TotalPlayerScores = new int[m_NumOfPlayers];

	D3DEngine::RenderEngine* m_RenderEngine;
	D3DEngine::PhysicsEngine* m_PhysicsEngine;

};