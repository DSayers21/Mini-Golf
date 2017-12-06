#include "MiniGolf.h"

#include "Level.h"

MiniGolf::MiniGolf()
{
}


void MiniGolf::Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine)
{
	int LevelNum = 4;

	//ZeroPadded
	int BlankData[7][7] = {
		{ 0, 0, 0, 0, 0, 0, 0 } ,
		{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 0
		{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 1
		{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 2
		{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 3
		{ 0, 0, 0, 0, 0, 0, 0 } ,   //Row 4
		{ 0, 0, 0, 0, 0, 0, 0 } ,
	};

	switch (LevelNum)
	{
		case -1:	//Original Test Level World
		{
			Level Test(m_Window, renderEngine, physicsEngine, GetRootObject());
			GetRootObject()->ClearGameObject();
			renderEngine->ResetEngine();
			Test.Destroy();
		
			break;
		}
		case 0:
		{
			//ZeroPadded
			int LevelData[7][7] = {
				{ 0, 0, 0, 0, 0, 0, 0 } ,
				{ 0, 0, 1, 1, 3, 0, 0 } ,  //Row 0
				{ 0, 0, 1, 0, 0, 0, 0 } ,  //Row 1
				{ 0, 0, 1, 1, 1, 0, 0 } ,  //Row 2
				{ 0, 0, 0, 0, 1, 0, 0 } ,  //Row 3
				{ 0, 0, 2, 1, 1, 0, 0 } ,   //Row 4
				{ 0, 0, 0, 0, 0, 0, 0 } ,
			};
			Level Test(LevelData, m_Window, renderEngine, physicsEngine, GetRootObject());
			GetRootObject()->ClearGameObject();
			renderEngine->ResetEngine();
			Test;
			Test.Destroy();
			break;
		}
		case 1:
		{
			//ZeroPadded
			int LevelData[7][7] = {
					{ 0, 0, 0, 0, 0, 0, 0 } ,
					{ 0, 1, 1, 2, 1, 1, 0 } ,  //Row 0
					{ 0, 1, 0, 1, 0, 1, 0 } ,  //Row 1
					{ 0, 1, 1, 1, 0, 1, 0 } ,  //Row 2
					{ 0, 1, 0, 0, 3, 1, 0 } ,  //Row 3
					{ 0, 1, 1, 1, 1, 1, 0 } ,   //Row 4
					{ 0, 0, 0, 0, 0, 0, 0 } ,
			};
			Level Test(LevelData, m_Window, renderEngine, physicsEngine, GetRootObject());
			GetRootObject()->ClearGameObject();
			renderEngine->ResetEngine();
			Test;
			Test.Destroy();
			break;
		}
		case 2:
		{
			//ZeroPadded
			int LevelData[7][7] = {
				{ 0, 0, 0, 0, 0, 0, 0 } ,
				{ 0, 3, 0, 1, 1, 1, 0 } ,  //Row 0
				{ 0, 1, 0, 1, 0, 1, 0 } ,  //Row 1
				{ 0, 1, 0, 2, 0, 1, 0 } ,  //Row 2
				{ 0, 1, 0, 0, 0, 1, 0 } ,  //Row 3
				{ 0, 1, 1, 1, 1, 1, 0 } ,   //Row 4
				{ 0, 0, 0, 0, 0, 0, 0 } ,
			};
			Level Test(LevelData, m_Window, renderEngine, physicsEngine, GetRootObject());
			break;
		}
		case 3:
		{
			//ZeroPadded
			int LevelData[7][7] = {
				{ 0, 0, 0, 0, 0, 0, 0 } ,
				{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 0
				{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 1
				{ 0, 0, 0, 2, 0, 0, 0 } ,  //Row 2
				{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 3
				{ 0, 0, 0, 0, 0, 0, 0 } ,   //Row 4
				{ 0, 0, 0, 0, 0, 0, 0 } ,
			};
			Level Test(LevelData, m_Window, renderEngine, physicsEngine, GetRootObject());
			break;
		}
		case 4:
		{
			//ZeroPadded
			int LevelData[7][7] = {
				{ 0, 0, 0, 0, 0, 0, 0 } ,
				{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 0
				{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 1
				{ 0, 0, 0, 2, 0, 0, 0 } ,  //Row 2
				{ 0, 0, 0, 0, 0, 0, 0 } ,  //Row 3
				{ 0, 0, 0, 0, 0, 0, 0 } ,   //Row 4
				{ 0, 0, 0, 0, 0, 0, 0 } ,
			};
			Level Test(LevelData, m_Window, renderEngine, physicsEngine, GetRootObject());
			GetRootObject()->ClearGameObject();
			renderEngine->ResetEngine();
			//Test;
			Test.Destroy();
			break;
		}
	}


	//Level Test(m_Window, renderEngine, physicsEngine, GetRootObject());
}

void MiniGolf::Input(D3DEngine::GetInput* input, float Delta)
{
	input->Update();

	m_RootObject->Input(input, Delta);
}