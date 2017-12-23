//Includes
#include "GameComponent.h"
#include "RenderEngine.h"
#include "Shader.h"
#include "GameObject.h"

namespace D3DEngine
{
	GameComponent::GameComponent()
	{
		//Empty
	}

	GameComponent::~GameComponent()
	{
		//Display Message
		std::cerr << "Destructor: Game Component" << std::endl;
	}

	void GameComponent::Input(GetInput* input, float Delta)
	{
		//Empty, (Implemented in child classes)
	}

	void GameComponent::Update(float Delta)
	{
		//Empty, (Implemented in child classes)
	}

	void GameComponent::Draw(Shader* shader, RenderEngine* renderEngine)
	{
		//Empty, (Implemented in child classes)
	}

	void GameComponent::AddToEngine(MainComp * mainComp)
	{
		//Empty, (Implemented in child classes)
	}
}