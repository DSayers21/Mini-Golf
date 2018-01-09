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

	//Close server and clients
	TClient.Terminate();
	if(m_ServerThread.joinable())
		m_ServerThread.join();
}

void MiniGolf::Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine)
{
	//Set the two pointers to point at the games rendering and physics handeling components
	m_RenderEngine = renderEngine;
	m_PhysicsEngine = physicsEngine;

	//Set Default amount of players as 2
	m_NumOfPlayers = 2;
	m_TotalPlayerScores = new int[m_NumOfPlayers];


	//Server Mode Button
	m_ServerMode = Button("Server Mode", 100, 300, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);
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
	m_QuitGame = Button("Quit Game", m_RenderEngine->GetWindow()->GetWidth() - 115, 29, 24, 58, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);

	//Initalise the ScoreBoard return to main menu Button
	m_MainMenu = Button("Main Menu", 100, 150, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);

	//Server Menu Buttons
	m_StartClient = Button("Start Client", 100, 250, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);
	m_StartServer = Button("Start Server", 100, 300, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);
	m_BackTMM = Button("Back to Main Menu", 100, 100, 24, 120, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);
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
		//Check if the server mode button has been pressed
		if (m_ServerMode.Input(input, m_Window->GetHeight()))
		{
			//Clean the UI 
			m_RenderEngine->RemoveAllText();
			m_GameState = GameState::SERVERMODE;
			return;
		}
	}

	if (m_GameState == SERVERMODE)
	{
		//Check if the return to main menu button is pressed
		if (m_BackTMM.Input(input, m_Window->GetHeight()))
		{
			//Clean the UI 
			m_RenderEngine->RemoveAllText();
			//Set to indicate the game is now at the main menu
			m_GameState = GameState::MAINMENU;
		}

		//Check if the start client button has been clicked
		if (m_StartClient.Input(input, m_Window->GetHeight()))
		{
			//Get IP Address to connect to
			std::string IPAddress;
			std::cerr << "Enter IP > ";
			std::cin >> IPAddress;

			//Get the port number to connect to
			std::string Port;
			std::cerr << "Enter Port > ";
			std::cin >> Port;

			//Connect the client to the server
			TClient.Start(IPAddress.c_str(), Port.c_str());
			//Start the interaction with the server
			TClient.Interact();
		}

		//Check if the start server button has been clicked
		if (m_StartServer.Input(input, m_Window->GetHeight()))
		{
			//Check if server has not yet been started
			if (!m_ServerStarted)
			{
				//Get the port to start the server on
				std::string Port = "5555";
				std::cerr << "Enter Port > ";
				std::cin >> Port;

				//Start the server in a new thread
				m_ServerThread = std::thread(ServerThread::CreateServerThread, Port);
				//Set server started to true
				m_ServerStarted = true;
				//Set the button to being clicked on
				m_StartServer.SetActive(true);
			}
		}
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

	//Send Messages
	if (input->GetKeyDown(D3DEngine::KEY_SPACE)) TClient.SendThis("SPAC");
	if (input->GetKeyDown(D3DEngine::KEY_LEFT)) TClient.SendThis("LEFT");
	if (input->GetKeyDown(D3DEngine::KEY_RIGHT)) TClient.SendThis("RIGH");
	if (input->GetKeyDown(D3DEngine::KEY_UP)) TClient.SendThis("UP");
	if (input->GetKeyDown(D3DEngine::KEY_DOWN)) TClient.SendThis("DOWN");

	//Process Received Messages
	if (TClient.GetLstReceived() == "SPAC") std::cerr << "HELLO DEAN YOU PRESSED SPACE" << std::endl;
	if (TClient.GetLstReceived() == "LEFT") std::cerr << "HELLO DEAN YOU PRESSED LEFT"  << std::endl;
	if (TClient.GetLstReceived() == "RIGH") std::cerr << "HELLO DEAN YOU PRESSED RIGH"  << std::endl;
	if (TClient.GetLstReceived() == "UP")	 std::cerr << "HELLO DEAN YOU PRESSED UP"	 << std::endl;
	if (TClient.GetLstReceived() == "DOWN") std::cerr << "HELLO DEAN YOU PRESSED DOWN"  << std::endl;

	//Update Inputs
	if (TClient.GetLstReceived() == "SPAC") input->SetKeyDown(D3DEngine::KEY_SPACE, true);
	if (TClient.GetLstReceived() == "LEFT") input->SetKeyDown(D3DEngine::KEY_LEFT, true);
	if (TClient.GetLstReceived() == "RIGH") input->SetKeyDown(D3DEngine::KEY_RIGHT, true);
	if (TClient.GetLstReceived() == "UP") input->SetKeyDown(D3DEngine::KEY_UP, true);
	if (TClient.GetLstReceived() == "DOWN") input->SetKeyDown(D3DEngine::KEY_DOWN, true);

	//Reset last message
	TClient.SetLstReceived("NULL");

	//Get Input for all objects in scene
	m_RootObject->Input(input, Delta);
}

void MiniGolf::Update(float Delta)
{
	//Update all the objects currently in the level
	GetRootObject()->Update(Delta);

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
				//Clear UI
				m_RenderEngine->RemoveAllText();
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
	//Render all the current objects loaded
	renderEngine->Render(GetRootObject());

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
		//Render the server mode button
		m_ServerMode.Render(renderEngine);
	}

	//If the menu is in server mode
	if (m_GameState == SERVERMODE)
	{
		//Add the title to the UI
		m_RenderEngine->AddText("TITLE", D3DEngine::TextToRender("Mini-Golf: Main Menu", D3DEngine::Vector3f(0, 255, 0),
			m_Window->GetWidth() / 2 - 120, m_Window->GetHeight() - 140));
		
		//Render Option Buttons
		m_StartClient.Render(renderEngine);
		m_StartServer.Render(renderEngine);
		
		//Render Main Menu Button
		m_BackTMM.Render(renderEngine);
	}

	//If in game then render game UI buttons
	if (m_GameState == GameState::GAME)
		m_QuitGame.Render(renderEngine);
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