#include "MiniGolf.h"

MiniGolf::MiniGolf()
{
	m_Course = GolfCourse("Courses/CourseOne.txt");
}

MiniGolf::~MiniGolf()
{
	std::cerr << "Destructor: MiniGolf" << std::endl;
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
			std::cout << "No more holes, looped back to start!" << std::endl;
		//Load the next hole
		LoadLevel(m_Course.GetCurrentHole());
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
			std::cout << "No more holes, looped back to start!" << std::endl;
		//Load the next hole
		LoadLevel(m_Course.GetCurrentHole());
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
			std::string Name = "PLAYER" + std::to_string(PlrID) + "SCORE";
			std::string Text = "Player " + std::to_string(i + 1) + " Final Score: " + std::to_string(Players[i]->GetScore());
			m_RenderEngine->AddText(Name, D3DEngine::TextToRender(Text, D3DEngine::Vector3f(255, 0, 255), 5, Y));
		}
		//Wait to reset until next update
		m_MoveToNextLevel = 10;
		Draw(m_RenderEngine);
		//m_RenderEngine->RenderText();
	}
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