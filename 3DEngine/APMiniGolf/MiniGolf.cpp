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
	LevelEmpty = false;
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

bool MiniGolf::LoadLevel(int LevelNum)
{
	m_CurrentLevel = new Level(m_Course.GetLevel(LevelNum).m_LevelData, m_Window, m_RenderEngine, m_PhysicsEngine, GetRootObject());
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