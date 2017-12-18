#include "MiniGolf.h"

MiniGolf::MiniGolf()
{
}


void MiniGolf::Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine)
{
	m_RenderEngine = renderEngine;
	m_PhysicsEngine = physicsEngine;

	LoadLevel(3);
}

void MiniGolf::Input(D3DEngine::GetInput* input, float Delta)
{
	input->Update();
	bool Created = false;
	if (input->GetKeyDown(D3DEngine::KEY_1))
	{
		LoadLevel(1);
		Created = true;
	}
	if (input->GetKeyDown(D3DEngine::KEY_2))
	{
		LoadLevel(3);
		Created = true;
	}
	if (input->GetKeyDown(D3DEngine::KEY_3))
	{
		ResetLevel();
	}
	if(!Created)
		m_RootObject->Input(input, Delta);
}

bool MiniGolf::LoadLevel(int LevelNum)
{
	bool TestWorld = false;
	int LevelData[7][7];
	LevelArray NewLevel;

	switch (LevelNum)
	{
		case -1:	//Original Test Level World
		{
			TestWorld = true;
			m_CurrentLevel = new Level(m_Window, m_RenderEngine, m_PhysicsEngine, GetRootObject());
			break;
		}
		case 0:
		{
			//ZeroPadded
			int NewLevelData[7][7] = {
				{ 0, 0, 0, 0, 0, 0, 0 } ,
				{ 0, 0, 1, 1, 3, 0, 0 } ,  //Row 0
				{ 0, 0, 1, 0, 0, 0, 0 } ,  //Row 1
				{ 0, 0, 1, 1, 1, 0, 0 } ,  //Row 2
				{ 0, 0, 0, 0, 1, 0, 0 } ,  //Row 3
				{ 0, 0, 2, 1, 1, 0, 0 } ,   //Row 4
				{ 0, 0, 0, 0, 0, 0, 0 } ,
			};
			NewLevel.SetLevelData(NewLevelData);
			break;
		}
		case 1:
		{
			//ZeroPadded
			int NewLevelData[7][7] = {
				{ 0, 0, 0, 0, 0, 0, 0 } ,
				{ 0, 1, 1, 2, 1, 1, 0 } ,  //Row 0
				{ 0, 1, 0, 1, 0, 1, 0 } ,  //Row 1
				{ 0, 1, 1, 1, 0, 1, 0 } ,  //Row 2
				{ 0, 1, 0, 0, 3, 1, 0 } ,  //Row 3
				{ 0, 1, 1, 1, 1, 1, 0 } ,   //Row 4
				{ 0, 0, 0, 0, 0, 0, 0 } ,
			};
			NewLevel.SetLevelData(NewLevelData);
			break;
		}
		case 2:
		{
			//ZeroPadded
			int NewLevelData[7][7] = {
				{ 0, 0, 0, 0, 0, 0, 0 } ,
				{ 0, 3, 0, 1, 1, 1, 0 } ,  //Row 0
				{ 0, 1, 0, 1, 0, 1, 0 } ,  //Row 1
				{ 0, 1, 0, 2, 0, 1, 0 } ,  //Row 2
				{ 0, 1, 0, 0, 0, 1, 0 } ,  //Row 3
				{ 0, 1, 1, 1, 1, 1, 0 } ,   //Row 4
				{ 0, 0, 0, 0, 0, 0, 0 } ,
			}; 
			NewLevel.SetLevelData(NewLevelData);
			break;
		}
		case 3:
		{
			//ZeroPadded
			int NewLevelData[7][7] = {
				{ 0, 0, 0, 0, 0, 0, 0 } ,
				{ 0, 3, 1, 1, 1, 0, 0 } ,  //Row 0
				{ 0, 0, 0, 0, 1, 0, 0 } ,  //Row 1
				{ 0, 0, 1, 2, 1, 0, 0 } ,  //Row 2
				{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 3
				{ 0, 0, 0, 0, 0, 0, 0 } ,   //Row 4
				{ 0, 0, 0, 0, 0, 0, 0 } ,
			};
			NewLevel.SetLevelData(NewLevelData);
			break;
		}
		case 4:
		{
			//ZeroPadded
			int NewLevelData[7][7] = {
				{ 0, 0, 0, 0, 0, 0, 0 } ,
				{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 0
				{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 1
				{ 0, 0, 0, 2, 0, 0, 0 } ,  //Row 2
				{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 3
				{ 0, 0, 0, 0, 0, 0, 0 } ,   //Row 4
				{ 0, 0, 0, 0, 0, 0, 0 } ,
			};
			NewLevel.SetLevelData(NewLevelData);
			break;
		}
	}
	
	D3DEngine::GameObject* Temp = GetRootObject();
	if (!TestWorld)
		m_CurrentLevel = new Level(NewLevel.m_LevelData, m_Window, m_RenderEngine, m_PhysicsEngine, GetRootObject());
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