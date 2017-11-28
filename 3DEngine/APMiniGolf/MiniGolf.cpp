#include "MiniGolf.h"

#include "Level.h"

MiniGolf::MiniGolf()
{
}


MiniGolf::~MiniGolf()
{
}

void MiniGolf::Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine)
{
	int LevelData[5][5] = {
		{ 0, 0, 0, 0, 0 } ,  //Row 0
		{ 0, 0, 1, 0, 0 } ,  //Row 1
		{ 0, 0, 2, 0, 0 } ,  //Row 2
		{ 0, 0, 1, 0, 0 } ,  //Row 3
		{ 0, 0, 0, 0, 0 }    //Row 4
	};

	Level Test(LevelData, m_Window, renderEngine, physicsEngine, GetRootObject());

	//Level Test(m_Window, renderEngine, physicsEngine, GetRootObject());
}

void MiniGolf::Input(D3DEngine::GetInput* input, float Delta)
{
	input->Update();

	m_RootObject->Input(input, Delta);
}