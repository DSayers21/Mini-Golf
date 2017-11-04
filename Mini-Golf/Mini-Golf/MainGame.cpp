#include "MainGame.h"
#include <cmath>
MainGame::MainGame()
{
	m_Lighting.InitLights();
	m_Shader = new D3DEngine::Shader("./Shaders/ColourShading");

	D3DEngine::Vertex Vertices[3] = { 
		D3DEngine::vec3(-0.5,-0.5,0),						 
		D3DEngine::vec3(0,0.5,0),	 
		D3DEngine::vec3(0.5,-0.5,0)
	};

	m_Mesh = new D3DEngine::Mesh(Vertices, sizeof(Vertices)/sizeof(Vertices[0]));


	int Test[6] = {20,60,90,180,270,360};
	int Count = 0;
	int Increment = 3;
	float Width = 0.01;

	for (int i = 0; i < SinTest; i++)
	{
		float Val = (Count) * (3.142 / 180);
		float Y = sin(Val);
		m_Cuboids[i] = D3DEngine::Cuboid(Width, Y, 0.1, D3DEngine::vec3(Width, 0, 0));
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
		//m_Cuboids[i].Draw();
	}

	m_Mesh->Draw();

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

void MainGame::MouseMovement(int x, int y)
{
	if(m_LastMouseX < x)
		m_MainCamera.SetCamR(true);
	else
		m_MainCamera.SetCamR(false);
	
	if (m_LastMouseX > x)
		m_MainCamera.SetCamL(true);
	else
		m_MainCamera.SetCamL(false);

	if (m_LastMouseY < y)
		m_MainCamera.SetCamU(true);
	else
		m_MainCamera.SetCamU(false);

	if (m_LastMouseY > y)
		m_MainCamera.SetCamD(true);
	else
		m_MainCamera.SetCamD(false);


	m_LastMouseX = x;
	m_LastMouseY = y;
}

void MainGame::MouseClick(int But, int State, int x, int y)
{
	if (State == 1) //Mouse Released
	{
		m_MainCamera.SetCamR(false);
		m_MainCamera.SetCamL(false);
		m_MainCamera.SetCamU(false);
		m_MainCamera.SetCamD(false);
	}
	switch (But)
	{
		case 0: 
		//Left Mouse

		break;
		case 1:
		//Wheel Click

		break;
		case 2:
		//Right Mouse

		break;
	}
}

void MainGame::UpdateScene(int ms)
{
	//Do Updates

	//End - Do Updates
	m_MainCamera.DoCamera(ms);
}