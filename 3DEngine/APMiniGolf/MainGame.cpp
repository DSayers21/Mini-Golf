#include "MainGame.h"
#include "MainComp.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

void MainGame::Init(D3DEngine::RenderEngine* renderEngine)
{

}

void MainGame::Input(D3DEngine::GetInput* input, float Delta)
{
	GetRootObject()->Input(input, Delta);
}

void MainGame::Update(float Delta)
{
	GetRootObject()->Update(Delta);
}

void MainGame::Draw(D3DEngine::RenderEngine* renderEngine)
{
	renderEngine->Render(GetRootObject());
}

void MainGame::SetWindow(D3DEngine::Window * Window)
{
	m_Window = Window;
	m_RootObject = new D3DEngine::GameObject();
}

void MainGame::SetEngine(D3DEngine::MainComp* mainComp)
{
	GetRootObject()->SetEngine(mainComp);
}