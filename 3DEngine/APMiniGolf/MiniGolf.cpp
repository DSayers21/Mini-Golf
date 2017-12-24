//Includes
#include "MiniGolf.h"

//Constructor
MiniGolf::MiniGolf()
{
	//Empty
}

MiniGolf::~MiniGolf()
{
	//Display message
	std::cerr << "Destructor: MiniGolf" << std::endl;
	//If the level needs to be deleted, then delete it
	if(m_GameState == GameState::GAME)
		ResetLevel();
	//Delete the players
	delete[] m_TotalPlayerScores;
}

void MiniGolf::Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine)
{
	//Set the two pointers to point at the games rendering and physics handeling components
	m_RenderEngine = renderEngine;
	m_PhysicsEngine = physicsEngine;

	//Set Default amount of players as 2
	m_NumOfPlayers = 2;
	m_TotalPlayerScores = new int[m_NumOfPlayers];

	//Initalise the player options set of buttons
	m_PlayerOptions.AddButton(Button("One Player", 100, 250, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false));
	m_PlayerOptions.AddButton(Button("Two Players", 250, 250, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), true));
	m_PlayerOptions.AddButton(Button("Four Players", 400, 250, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false));
	m_PlayerOptions.AddButton(Button("Sixteen Players", 550, 250, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false));
	//Initalise the course options set of buttons
	m_CourseFileName = "Courses/CourseOne.txt";
	m_CourseOptions.AddButton(Button("Course One", 100, 200, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), true));
	m_CourseOptions.AddButton(Button("Course Two", 250, 200, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false));
	m_CourseOptions.AddButton(Button("Course Three", 400, 200, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false));
	//Initalise the Start Game button
	m_StartGame = Button("Start Game", 100, 150, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);
	//Exit Game button
	m_ExitGame = Button("Exit", 100, 100, 24, 24, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);

	//In game buttons
	m_QuitGame = Button("Quit Game", m_RenderEngine->GetWindow()->GetWidth() - 160, 50, 24, 58, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);

	//Initalise the ScoreBoard return to main menu Button
	m_MainMenu = Button("Main Menu", 100, 150, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);
}

void MiniGolf::Input(D3DEngine::GetInput* input, float Delta)
{
	//Update the Input object
	input->Update();

	//Check if in the main menu screen
	if (m_GameState == GameState::MAINMENU)
	{
		//Get the input from the player options set of buttons
		std::string ButtonPressedName = m_PlayerOptions.InputButtons(input, m_Window->GetHeight());
		if(ButtonPressedName != "NULL")
		{
			//Update the number of players depending on which player button was pressed
			if(ButtonPressedName == "One Player") m_NumOfPlayers = 1;
			if (ButtonPressedName == "Two Players") m_NumOfPlayers = 2;
			if (ButtonPressedName == "Four Players") m_NumOfPlayers = 4;
			if (ButtonPressedName == "Sixteen Players") m_NumOfPlayers = 16;
			//Update Player Score Array
			delete[] m_TotalPlayerScores;
			m_TotalPlayerScores = new int[m_NumOfPlayers];
		}
		//Get the input from the Course options set of buttons
		ButtonPressedName = m_CourseOptions.InputButtons(input, m_Window->GetHeight());
		if (ButtonPressedName != "NULL")
		{
			//Update the course number depending on which Course button was pressed
			if (ButtonPressedName == "Course One") m_CourseFileName = "Courses/CourseOne.txt";
			if (ButtonPressedName == "Course Two") m_CourseFileName = "Courses/CourseTwo.txt";
			if (ButtonPressedName == "Course Three") m_CourseFileName = "Courses/CourseThree.txt";
		}
		//Check if the start game button was pressed
		if (m_StartGame.Input(input, m_Window->GetHeight()))
		{
			//Clean the UI 
			m_RenderEngine->RemoveAllText();
			//Load the selected course data
			m_Course = GolfCourse(m_CourseFileName);

			//Set all total scores to 0
			for (int i = 0; i < m_NumOfPlayers; i++)
				m_TotalPlayerScores[i] = 0;
			//Set to indicate the game is in the game state
			m_GameState = GameState::GAME;
			//Load the first Level from the course
			LoadLevel(0);
		}
		//Check if the exit game button has been pressed
		if (m_ExitGame.Input(input, m_Window->GetHeight()))
			m_Window->Close(); //Close the window
	}

	//In game menu buttons
	if (m_GameState == GameState::GAME)
	{
		//Check if the return to main menu button is pressed
		if (m_QuitGame.Input(input, m_Window->GetHeight()))
		{
			//Delete Level
			ResetLevel();

			//Clean the UI 
			m_RenderEngine->RemoveAllText();
			//Set to indicate the game is now at the main menu
			m_GameState = GameState::MAINMENU;
		}
	}

	//Check if the game is in the scoreboard screen
	if (m_GameState == GameState::SCOREBOARD)
	{
		//Check if the return to main menu button is pressed
		if (m_MainMenu.Input(input, m_Window->GetHeight()))
		{
			//Clean the UI 
			m_RenderEngine->RemoveAllText();
			//Set to indicate the game is now at the main menu
			m_GameState = GameState::MAINMENU;
		}
	}

	//Get Input for all objects in scene
	m_RootObject->Input(input, Delta);
}

void MiniGolf::Update(float Delta)
{
	//Check if the game state is game
	if (m_GameState == GameState::GAME)
	{
		//Check if the game needs to move to the next level yet
		if (m_MoveToNextLevel == -1)
		{
			//Set back to default
			m_MoveToNextLevel = -2;
			//Reset Level
			ResetLevel();
			//Progress to next hole
			bool IsReset = m_Course.NextHole();
			if (!IsReset)
			{
				//Display message
				std::cout << "No more holes! Course Finished" << std::endl;
				//Update game state
				m_GameState = GameState::SCOREBOARD;
			}
			else
			{
				//Load the next hole
				LoadLevel(m_Course.GetCurrentHole());
			}
		}
		else if (m_MoveToNextLevel >= 0) //Otherwise update the move to next level counter
			m_MoveToNextLevel--;

		//Update all the objects currently in the level
		GetRootObject()->Update(Delta);

		//Update the current level, if it returns true the ball has been putted
		if (m_CurrentLevel->Update(Delta))
		{
			//Get all the players data from the hole
			std::vector<Player*> Players = m_CurrentLevel->GetPlayers();
			//Loop over all the players to display their score
			for (int i = 0; i < Players.size(); i++)
			{
				int PlrID = Players[i]->GetID();			//Get the player ID
				int Y = 5 + (PlrID * 24);					//Get the Y position of the current player
				int PlayerScore = Players[i]->GetScore();	//Get the current players score
				m_TotalPlayerScores[i] += PlayerScore;		//Update the current players total score
				//Get the name and text to update the UI
				std::string Name = "PLAYER" + std::to_string(PlrID) + "SCORE";
				std::string Text = "Player " + std::to_string(i + 1) + " Final Score: " + std::to_string(PlayerScore);
				//Update the UI
				m_RenderEngine->AddText(Name, D3DEngine::TextToRender(Text, D3DEngine::Vector3f(255, 0, 255), 5, Y));
			}
			//Wait to reset until next update
			m_MoveToNextLevel = m_Delay;
		}
	}
	//Check if the game is in the scoreboard state
	if (m_GameState == GameState::SCOREBOARD)
	{
		//Add the title Score Board to the UI
		m_RenderEngine->AddText("SCORETITLE", D3DEngine::TextToRender("Score Board", D3DEngine::Vector3f(150, 0, 255),
			m_Window->GetCenter().GetX() - 55, (m_Window->GetHeight() - 124)));

		//Loop over all the players
		for (int i = 0; i < m_NumOfPlayers; i++)
		{
			int PlrID = i + 1;											//Get the player ID
			int Y = (m_Window->GetHeight() - 150) - (PlrID * 24);		//Get the Y position of the current player
			//Get the name and text to update the UI
			std::string Name = "PLAYER" + std::to_string(PlrID) + "SCORE";
			std::string Text = "Player " + std::to_string(i + 1) + " Total Score: " + std::to_string(m_TotalPlayerScores[i]);
			//Update the UI
			m_RenderEngine->AddText(Name, D3DEngine::TextToRender(Text, D3DEngine::Vector3f(255, 0, 255), m_Window->GetCenter().GetX() - 110, Y));
		}
	}
}

void MiniGolf::Draw(D3DEngine::RenderEngine* renderEngine)
{
	//Check if at the MainMenu
	if (m_GameState == GameState::MAINMENU)
	{
		//Add the title to the UI
		m_RenderEngine->AddText("TITLE", D3DEngine::TextToRender("Mini-Golf: Main Menu", D3DEngine::Vector3f(0,255,0), 
			m_Window->GetWidth()/2-120, m_Window->GetHeight()-140));
		//Draw Player Number Buttons
		m_PlayerOptions.RenderButtons(renderEngine);
		//Draw Course Number Buttons
		m_CourseOptions.RenderButtons(renderEngine);
		//Draw the start button to the screen
		m_StartGame.Render(renderEngine);
		//Render the exit game button
		m_ExitGame.Render(renderEngine);
	}

	//If in game then render game UI buttons
	if (m_GameState == GameState::GAME)
		m_QuitGame.Render(renderEngine);

	//If course is finished, render return to main menu button
	if (m_GameState == GameState::SCOREBOARD)
		m_MainMenu.Render(renderEngine);

	//Render all the current objects loaded
	renderEngine->Render(GetRootObject());
}

bool MiniGolf::LoadLevel(int LevelNum)
{
	//Load the current hole with the correct amount of players
	m_CurrentLevel = new Level(m_NumOfPlayers, m_Course.GetLevel(LevelNum).m_LevelData, m_Window, m_RenderEngine, m_PhysicsEngine, GetRootObject());
	return true;
}

void MiniGolf::ResetLevel()
{
	//Clear all the level objects
	GetRootObject()->ClearGameObject();
	//Reset the rendering engine
	m_RenderEngine->ResetEngine();
	//Reset the physics engine
	m_PhysicsEngine->ClearObjects();
	//Delete the level
	m_CurrentLevel->Destroy();
	delete m_CurrentLevel;
}