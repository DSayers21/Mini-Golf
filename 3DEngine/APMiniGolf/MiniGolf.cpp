#include "MiniGolf.h"

MiniGolf::MiniGolf()
{
	m_NumOfPlayers = 2;

	m_OnePlayer = Rectangle("One Player", 100, 250, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);
	m_TwoPlayer = Rectangle("Two Players", 250, 250, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), true);
	m_FourPlayer = Rectangle("Four Players", 400, 250, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);
	m_SixteenPlayer = Rectangle("Sixteen Players", 550, 250, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);
	
	m_CourseFileName = "Courses/CourseOne.txt";
	m_CourseOne = Rectangle("Course One", 100, 200, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), true);
	m_CourseTwo = Rectangle("Course Two", 250, 200, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);
	m_CourseThree = Rectangle("Course Three", 400, 200, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);

	m_StartGame = Rectangle("Start Game", 100, 150, 24, 68, D3DEngine::Vector3f(255,0,0), D3DEngine::Vector3f(0, 255, 0), false);

	//ScoreBoard Button
	m_MainMenu = Rectangle("Main Menu", 100, 150, 24, 68, D3DEngine::Vector3f(255, 0, 0), D3DEngine::Vector3f(0, 255, 0), false);
}

MiniGolf::~MiniGolf()
{
	std::cerr << "Destructor: MiniGolf" << std::endl;
	if((!m_CourseFinished)&&(!m_Menu))
		ResetLevel();
}

void MiniGolf::Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine)
{
	m_RenderEngine = renderEngine;
	m_PhysicsEngine = physicsEngine;
}

void MiniGolf::Input(D3DEngine::GetInput* input, float Delta)
{
	//Update the Input object
	input->Update();
	if (m_Menu)
	{
		if (m_OnePlayer.Input(input, m_Window->GetHeight()))
		{
			m_OnePlayer.SetActive(true);
			m_TwoPlayer.SetActive(false);
			m_FourPlayer.SetActive(false);
			m_SixteenPlayer.SetActive(false);
			m_NumOfPlayers = 1;
		}

		if (m_TwoPlayer.Input(input, m_Window->GetHeight()))
		{
			m_TwoPlayer.SetActive(true);
			m_OnePlayer.SetActive(false);
			m_FourPlayer.SetActive(false);
			m_SixteenPlayer.SetActive(false);
			m_NumOfPlayers = 2;
		}
		if (m_FourPlayer.Input(input, m_Window->GetHeight()))
		{
			m_FourPlayer.SetActive(true);
			m_OnePlayer.SetActive(false);
			m_TwoPlayer.SetActive(false);
			m_SixteenPlayer.SetActive(false);
			m_NumOfPlayers = 4;
		}
		if (m_SixteenPlayer.Input(input, m_Window->GetHeight()))
		{
			m_SixteenPlayer.SetActive(true);
			m_OnePlayer.SetActive(false);
			m_TwoPlayer.SetActive(false);
			m_FourPlayer.SetActive(false);
			m_NumOfPlayers = 16;
		}
		if (m_CourseOne.Input(input, m_Window->GetHeight()))
		{
			m_CourseOne.SetActive(true);
			m_CourseTwo.SetActive(false);
			m_CourseThree.SetActive(false);
			m_CourseFileName = "Courses/CourseOne.txt";
		}
		if (m_CourseTwo.Input(input, m_Window->GetHeight()))
		{
			m_CourseOne.SetActive(false);
			m_CourseTwo.SetActive(true);
			m_CourseThree.SetActive(false);
			m_CourseFileName = "Courses/CourseTwo.txt";
		}
		if (m_CourseThree.Input(input, m_Window->GetHeight()))
		{
			m_CourseOne.SetActive(false);
			m_CourseTwo.SetActive(false);
			m_CourseThree.SetActive(true);
			m_CourseFileName = "Courses/CourseThree.txt";
		}
		if (m_StartGame.Input(input, m_Window->GetHeight()))
		{
			m_RenderEngine->RemoveAllText();
			m_Course = GolfCourse(m_CourseFileName);

			//Set all total scores to 0
			for (int i = 0; i < m_NumOfPlayers; i++)
				m_TotalPlayerScores[i] = 0;
			m_Menu = false;

			LoadLevel(0);
		}

	}

	if (m_CourseFinished)
	{
		if (m_MainMenu.Input(input, m_Window->GetHeight()))
		{
			//Return to main menu
			m_RenderEngine->RemoveAllText();
			m_Menu = true;
			m_CourseFinished = false;
		}
		
	}

	//Get Input for all objects in scene
	m_RootObject->Input(input, Delta);
	
}

void MiniGolf::Update(float Delta)
{
	if (!m_Menu)
	{
		if (m_MoveToNextLevel == -1)
		{
			m_MoveToNextLevel = -2;
			//Reset Level
			ResetLevel();
			//Progress to next hole
			bool IsReset = m_Course.NextHole();
			if (!IsReset)
			{
				std::cout << "No more holes! Course Finished" << std::endl;
				m_CourseFinished = true;
			}
			else
			{
				//Load the next hole
				LoadLevel(m_Course.GetCurrentHole());
			}
		}
		else if (m_MoveToNextLevel >= 0)
			m_MoveToNextLevel--;

		GetRootObject()->Update(Delta);
		if (m_CurrentLevel->Update(Delta))
		{
			std::vector<Player*> Players = m_CurrentLevel->GetPlayers();

			for (int i = 0; i < Players.size(); i++)
			{
				int PlrID = Players[i]->GetID();
				int Y = 5 + (PlrID * 24);
				int PlayerScore = Players[i]->GetScore();
				m_TotalPlayerScores[i] += PlayerScore;
				std::string Name = "PLAYER" + std::to_string(PlrID) + "SCORE";
				std::string Text = "Player " + std::to_string(i + 1) + " Final Score: " + std::to_string(PlayerScore);
				m_RenderEngine->AddText(Name, D3DEngine::TextToRender(Text, D3DEngine::Vector3f(255, 0, 255), 5, Y));
			}
			//Wait to reset until next update
			m_MoveToNextLevel = 10;
		}
		//If course is finished
		if (m_CourseFinished)
		{
			m_RenderEngine->AddText("SCORETITLE", D3DEngine::TextToRender("Score Board", D3DEngine::Vector3f(150, 0, 255),
				m_Window->GetCenter().GetX() - 55, (m_Window->GetHeight() - 124)));

			for (int i = 0; i < m_NumOfPlayers; i++)
			{
				int PlrID = i + 1;
				int Y = (m_Window->GetHeight() - 150) - (PlrID * 24);
				std::string Name = "PLAYER" + std::to_string(PlrID) + "SCORE";
				std::string Text = "Player " + std::to_string(i + 1) + " Total Score: " + std::to_string(m_TotalPlayerScores[i]);
				m_RenderEngine->AddText(Name, D3DEngine::TextToRender(Text, D3DEngine::Vector3f(255, 0, 255), m_Window->GetCenter().GetX() - 100, Y));
			}
		}
	}
}

void MiniGolf::Draw(D3DEngine::RenderEngine* renderEngine)
{
	if (m_Menu)
	{
		m_RenderEngine->AddText("TITLE", D3DEngine::TextToRender("Mini-Golf", D3DEngine::Vector3f(0,255,0), m_Window->GetWidth()/2-60, m_Window->GetHeight()-140));
		//Player Number Buttons
		m_OnePlayer.Render(renderEngine);
		m_TwoPlayer.Render(renderEngine);
		m_FourPlayer.Render(renderEngine);
		m_SixteenPlayer.Render(renderEngine);
		//Course Number Buttons
		m_CourseOne.Render(renderEngine);
		m_CourseTwo.Render(renderEngine);
		m_CourseThree.Render(renderEngine);

		m_StartGame.Render(renderEngine);
	}
	if (m_CourseFinished)
	{
		m_MainMenu.Render(renderEngine);
	}
	renderEngine->Render(GetRootObject());
}

bool MiniGolf::LoadLevel(int LevelNum)
{
	m_CurrentLevel = new Level(m_NumOfPlayers, m_Course.GetLevel(LevelNum).m_LevelData, m_Window, m_RenderEngine, m_PhysicsEngine, GetRootObject());
	return true;
}

void MiniGolf::ResetLevel()
{
	GetRootObject()->ClearGameObject();
	m_RenderEngine->ResetEngine();
	m_PhysicsEngine->ClearObjects();
	m_CurrentLevel->Destroy();
	delete m_CurrentLevel;
}