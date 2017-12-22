//Includes
#include "MainGame.h"
#include "MainComp.h"

MainGame::MainGame()
{
	//Empty
}

MainGame::~MainGame()
{
	//Display message
	std::cerr << "Destructor: Main Game" << std::endl;
	//Clear the root object (and therefore the scene)
	m_RootObject->ClearGameObject();
	//Delete the root object
	delete m_RootObject;
	//Delete the mesh list
	delete m_MeshList;
}

void MainGame::Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine)
{
	//Empty
}

void MainGame::Input(D3DEngine::GetInput* input, float Delta)
{
	//Do input for the scene
	GetRootObject()->Input(input, Delta);
}

void MainGame::Update(float Delta)
{
	//Do Update for the scene
	GetRootObject()->Update(Delta);
}

void MainGame::Draw(D3DEngine::RenderEngine* renderEngine)
{
	//Render the scene
	renderEngine->Render(GetRootObject());
}

void MainGame::SetWindow(D3DEngine::Window * Window)
{
	//Set the window
	m_Window = Window;
	//Setup the root object
	m_RootObject = new D3DEngine::GameObject();
	m_RootObject->GetTransform()->SetPosition(D3DEngine::Vector3f(0,0,0));
}

void MainGame::SetEngine(D3DEngine::MainComp* mainComp)
{
	//Set the MainComponent to the root object
	GetRootObject()->SetEngine(mainComp);
}