#include "MainGame.h"
#include <cmath>
MainGame::MainGame()
{
	m_Lighting.InitLights();
	m_Shader = new D3DEngine::Shader("./Shaders/ColourShading");
	int Test[6] = {20,60,90,180,270,360};
	int Count = 0;
	int Increment = 3;
	for (int i = 0; i < SinTest; i++)
	{
		float Val = (Count) * (3.142 / 180);
		float Y = sin(Val);
		m_Cuboids[i] = D3DEngine::Cuboid(0.1, Y, 0.1, D3DEngine::vec3(0.1, 0, 0));
		Count += Increment;
	}
}


MainGame::~MainGame()
{
}


void MainGame::RenderScene(void)
{
	//Draw Events
	//m_Shader->Bind();
	//glutSolidTeapot(.5);


	for (int i = 0; i < SinTest; i++)
	{
		m_Cuboids[i].Draw();
	}

	//m_Cuboid.Draw();
	//m_Cuboid2.Draw();
	//m_Rect.Draw();


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