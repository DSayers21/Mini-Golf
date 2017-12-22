#include "MiniGolf.h"

MiniGolf::MiniGolf()
{
	m_Course = GolfCourse("Courses/CourseThree.txt");

	//Set all total scores to 0
	for (int i = 0; i < m_NumOfPlayers; i++)
		m_TotalPlayerScores[i] = 0;
}

MiniGolf::~MiniGolf()
{
	std::cerr << "Destructor: MiniGolf" << std::endl;
	if(!m_CourseFinished)
		ResetLevel();
}


void MiniGolf::Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine)
{
	m_RenderEngine = renderEngine;
	m_PhysicsEngine = physicsEngine;


	LoadLevel(0);
}

void MiniGolf::Input(D3DEngine::GetInput* input, float Delta)
{
	//Update the Input object
	input->Update();

	//Check for manual next level progress
	if (input->GetKeyDown(D3DEngine::KEY_1))
	{
		//Reset Level
		ResetLevel();
		//Progress to next hole
		bool IsReset = m_Course.NextHole();
		if (!IsReset) 
			std::cout << "No more holes! Course Finished" << std::endl;
		else
		{
			//Load the next hole
			LoadLevel(m_Course.GetCurrentHole());
		}
	}

	//Get Input for all objects in scene
	m_RootObject->Input(input, Delta);
}

void MiniGolf::Update(float Delta)
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
	else if(m_MoveToNextLevel >= 0)
	{
		m_MoveToNextLevel--;
	}

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
			m_Window->GetCenter().GetX() - 55, (m_Window->GetHeight()-124)));

		for (int i = 0; i < m_NumOfPlayers; i++)
		{
			int PlrID = i+1;
			int Y = (m_Window->GetHeight() - 150) - (PlrID * 24);
			std::string Name = "PLAYER" + std::to_string(PlrID) + "SCORE";
			std::string Text = "Player " + std::to_string(i + 1) + " Total Score: " + std::to_string(m_TotalPlayerScores[i]);
			m_RenderEngine->AddText(Name, D3DEngine::TextToRender(Text, D3DEngine::Vector3f(255, 0, 255), m_Window->GetCenter().GetX()-100, Y));
		}
	}
}

void MiniGolf::Draw(D3DEngine::RenderEngine* renderEngine)
{
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