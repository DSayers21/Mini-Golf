#pragma once

//Includes
#include "MainGame.h"
#include "Level.h"
#include "GolfCourse.h"
#include "Menu.h"

//Enum to handle the current state of the game
enum GameState 
{
	MAINMENU,
	GAME,
	SCOREBOARD
};

//Inherits from base class main game
class MiniGolf : public MainGame
{
public:
	//Constructor and Destructor
	MiniGolf();
	virtual ~MiniGolf();
	//Function to initalise the game
	void Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine);
	//Input handles keyboard and mouse events
	void Input(D3DEngine::GetInput* input, float Delta);
	//Update checks the current state of the game
	void Update(float Delta);
	//Draw renders everything which is currently needing to be rendered
	void Draw(D3DEngine::RenderEngine* renderEngine);
	//Function to load in the current level
	bool LoadLevel(int LevelNum);
	//Destroys the current level allowing for another to be made
	void ResetLevel();

private:
	//Game State to keep track of the current state of the game e.g. Main Menu, game and scoreboard
	GameState m_GameState = GameState::MAINMENU;
	
	//Delay so when final ball is putted the level doesnt instantly change 
	//Allows for the scores to be updated and shown
	int m_MoveToNextLevel = -2;
	int m_Delay = 20;

	//Current Level
	GolfCourse m_Course;
	Level* m_CurrentLevel;

	//Main Menu Buttons
	Button m_ExitGame;
	Button m_StartGame;
	ButtonGroup m_PlayerOptions;
	ButtonGroup m_CourseOptions;

	//In game buttons
	Button m_QuitGame;

	//Score Board Buttons
	Button m_MainMenu;

	//Options
	int m_NumOfPlayers = 4;
	std::string m_CourseFileName = "";
	//Setup Total Scores Array
	int* m_TotalPlayerScores = nullptr;

	//Pointers to Render and Physics Engines
	D3DEngine::RenderEngine* m_RenderEngine;
	D3DEngine::PhysicsEngine* m_PhysicsEngine;
};