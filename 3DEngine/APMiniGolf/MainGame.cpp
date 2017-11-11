#include "MainGame.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{

}

void MainGame::Input(D3DEngine::Input& input, float Delta)
{
	m_RootObject->Input(Delta);
}

void MainGame::Update(float Delta)
{
	m_RootObject->Update(Delta);
}

void MainGame::Draw()
{

}

void MainGame::SetWindow(D3DEngine::Window * Window)
{
	m_Window = Window;
	//m_Input = new D3DEngine::Input(Window);
	m_RootObject = new D3DEngine::GameObject();
}