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

void MainGame::Input()
{
	m_RootObject->Input();
}

void MainGame::Update()
{
	m_RootObject->Update();
}

void MainGame::Draw()
{

}

void MainGame::SetWindow(D3DEngine::Window * Window)
{
	m_Window = Window;
	m_Input = new D3DEngine::Input(Window);
	m_Camera = new D3DEngine::Camera();
	m_RootObject = new D3DEngine::GameObject(m_Camera);
}