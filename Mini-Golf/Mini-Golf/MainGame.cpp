#include "MainGame.h"

MainGame::MainGame()
{
	m_Lighting.InitLights();
}


MainGame::~MainGame()
{
}


void MainGame::RenderScene(void)
{
	//Draw Events

	m_Cuboid.Draw();
	m_Cuboid2.Draw();
	m_Rect.Draw();


	//Set camera
	m_MainCamera.LookAt();
}

void MainGame::SpecKeyboardFunc(int key, int x, int y)
{
	switch (key)
	{

	}
}

void MainGame::SpecKeyboardUpFunc(int key, int x, int y)
{
	switch (key)
	{

	}
}

void MainGame::KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case(32):
	{
		m_MainCamera.SetCamRot(false);
		break;
	}
	case('z'):
	{
		m_MainCamera.SetCamL(true);
		break;
	}
	case('c'):
	{
		m_MainCamera.SetCamR(true);
		break;
	}
	case('s'):
	{
		m_MainCamera.SetCamU(true);
		break;
	}
	case('x'):
	{
		m_MainCamera.SetCamD(true);
		break;
	}
	case('f'):
	{
		m_MainCamera.SetCamZin(true);
		break;
	}
	case('v'):
	{
		m_MainCamera.SetCamZout(true);
		break;
	}
	}

}

void MainGame::KeyboardUpFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case(32):
	{
		m_MainCamera.SetCamRot(true);
		break;
	}
	case('z'):
	{
		m_MainCamera.SetCamL(false);
		break;
	}
	case('c'):
	{
		m_MainCamera.SetCamR(false);
		break;
	}
	case('s'):
	{
		m_MainCamera.SetCamU(false);
		break;
	}
	case('x'):
	{
		m_MainCamera.SetCamD(false);
		break;
	}
	case('f'):
	{
		m_MainCamera.SetCamZin(false);
		break;
	}
	case('v'):
	{
		m_MainCamera.SetCamZout(false);
		break;
	}
	}
}

void MainGame::UpdateScene(int ms)
{
	//Do Updates

	//End - Do Updates
	m_MainCamera.DoCamera(ms);
}