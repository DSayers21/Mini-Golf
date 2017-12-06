#include "MainGame.h"
#include "MainComp.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
	std::cerr << "Deleted Main Game" << std::endl;
	m_RootObject->ClearGameObject();
	delete m_RootObject;
	delete m_MeshList;
}

void MainGame::Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine)
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
	m_RootObject->GetTransform()->SetPosition(D3DEngine::Vector3f(0,0,0));
}

void MainGame::SetEngine(D3DEngine::MainComp* mainComp)
{
	GetRootObject()->SetEngine(mainComp);
}